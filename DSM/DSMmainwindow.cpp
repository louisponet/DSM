
#include <glm/gtx/norm.hpp>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "src/graphics/generator.h"
#include "DSMmainwindow.h"
#include "src/global.h"




Generator* Generator::gen_instance;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.tableWidget->reset();
    setAttribute(Qt::WA_DeleteOnClose);
	

}

MainWindow::~MainWindow()
{
    if (m_CreateStructureWindow != nullptr)
    {
        delete m_CreateStructureWindow;
    }
    for (int i = 0; i<m_Structures.size();i++)
    {
        delete m_Structures[i];
    }
}

//------------------------OPEN/CLOSING EXISTING STRUCTURES-------------------------//

void MainWindow::openStructure()
{
    QString path = QFileDialog::getOpenFileName(NULL, tr("Open File"), "", tr("Text files(*.txt;*.in)"));
    if (path == "")
    {
        return;
    }
    else
    {
        Structure* structure = new Structure();
        m_Structures.push_back(structure);
        m_SelectedStructure = m_Structures.size() - 1;
        std::vector<Particle> atoms;
        glm::dmat3 cell;
        m_QeHandler.loadIN(path, atoms, cell);
        m_Structures[m_SelectedStructure]->file = path;

        m_Structures[m_SelectedStructure]->name = path.mid(path.lastIndexOf("/") + 1,  path.lastIndexOf(".")-(path.lastIndexOf("/") + 1));
        m_Structures[m_SelectedStructure]->setCell(cell);
        m_Structures[m_SelectedStructure]->populateAtoms(atoms);
        ui.openGLWidget->setFocus();
        ui.treeWidget->addStructure(m_Structures[m_SelectedStructure]);
        ui.openGLWidget->addStructure(m_Structures[m_SelectedStructure]);

        displayStructure();
    }
    return;
}

void MainWindow::closeStructure()
{
    ui.treeWidget->removeStructure(m_Structures[m_SelectedStructure]);
    ui.openGLWidget->removeStructure(m_SelectedStructure);
    Generator::instance()->deleteStructureBuffers(m_Structures[m_SelectedStructure]);
    delete m_Structures[m_SelectedStructure];
    m_Structures.erase(m_Structures.begin() + m_SelectedStructure);
    m_SelectedStructure = m_Structures.size()-1;
    m_SelectedAtom = 100000;
    updateAtomSelection();
    displayStructure();

}

//------------------------DISPLAY MANIPULATION/SIGNAL HANDLING-------------------------//

void MainWindow::displayStructure()
{
    if (m_SelectedStructure != -1)
    {
        
        ui.spinBox->blockSignals(true);
        ui.spinBox->setValue(m_Structures[m_SelectedStructure]->v1NegImCount);
        ui.spinBox->blockSignals(false);
        ui.spinBox_2->blockSignals(true);
        ui.spinBox_2->setValue(m_Structures[m_SelectedStructure]->v1PosImCount);
        ui.spinBox_2->blockSignals(false);
        ui.spinBox_3->blockSignals(true);
        ui.spinBox_3->setValue(m_Structures[m_SelectedStructure]->v2NegImCount);
        ui.spinBox_3->blockSignals(false);
        ui.spinBox_4->blockSignals(true);
        ui.spinBox_4->setValue(m_Structures[m_SelectedStructure]->v2PosImCount);
        ui.spinBox_4->blockSignals(false);
        ui.spinBox_5->blockSignals(true);
        ui.spinBox_5->setValue(m_Structures[m_SelectedStructure]->v3NegImCount);
        ui.spinBox_5->blockSignals(false);
        ui.spinBox_6->blockSignals(true);
        ui.spinBox_6->setValue(m_Structures[m_SelectedStructure]->v3PosImCount);
        ui.spinBox_6->blockSignals(false);
        ui.openGLWidget->selectStructure(m_SelectedStructure);
        ui.openGLWidget->setFocus();
    }
    else
        ui.openGLWidget->selectStructure(m_SelectedStructure);
    setScales();
}

void MainWindow::displayMessage(QString message)
{
    QMessageBox* msg = new QMessageBox();
    msg->setAttribute(Qt::WA_DeleteOnClose);
    msg->setText(message);
    msg->exec();
}

void MainWindow::treewidgetSelection(QTreeWidgetItem* item)
{
    if (item->parent() != NULL)
    {
        QTreeWidgetItem* parent = item->parent();
        QString structure_name = parent->data(0, 0).toString();
        m_SelectedAtom = parent->indexOfChild(item);
        for (int i = 0; i < m_Structures.size(); i++)
        {
            if (structure_name == m_Structures[i]->name)
            {
                m_SelectedStructure = i;
            }
        }
    }
    else
    {
        QString structure_name = item->data(0, 0).toString();
        m_SelectedAtom = 100000;
        for (int i = 0; i < m_Structures.size(); i++)
        {
            if (structure_name == m_Structures[i]->name)
            {
                m_SelectedStructure = i;
            }
        }

    }
    updateAtomSelection();
    displayStructure();

}

void MainWindow::menuActionTriggered(QAction* item)
{
    if (item->text() == "Create new Structure")
    {
        if (m_CreateStructureWindow != nullptr)
        {
            delete m_CreateStructureWindow;
        }
        if (tmp_Structure)
            delete tmp_Structure;
        tmp_Structure = new Structure();
        tmp_Structure->isnew = true;
        m_CreateStructureWindow = new CreateStructureWindow(tmp_Structure);

        QObject::connect(m_CreateStructureWindow, SIGNAL(structureCreated(Structure*)), this, SLOT(acceptStructure(Structure*)));
        QObject::connect(m_CreateStructureWindow, SIGNAL(destroyStructure()), this, SLOT(deleteNewStructure()));

        m_CreateStructureWindow->show();
    }
    else if (item->text() == "Open File")
    {
        openStructure();
    }
//----------------These are all the possible actions that can be performed on open structures-------------------//
    if (m_SelectedStructure != -1)
    {
        if (item->text() == "Close")
        {

            if (m_Structures[m_SelectedStructure]->edited)
            {
                QMessageBox* messagebox = new QMessageBox;
                messagebox->setText("Structure was edited, closing it will destroy all changes.\nAre you sure?");
                messagebox->setAttribute(Qt::WA_DeleteOnClose);
                QPushButton *yesButton = messagebox->addButton(QMessageBox::Yes);
                QPushButton *cancelButton = messagebox->addButton(QMessageBox::Cancel);
                QObject::connect(yesButton, SIGNAL(clicked()), this, SLOT(closeStructure()));
                QObject::connect(cancelButton, SIGNAL(clicked()), messagebox, SLOT(close()));
                messagebox->show();
            }
            else
                closeStructure();
        }

        else  if (item->text() == "Save")
        {

            if (!m_Structures[m_SelectedStructure]->edited)
            {
                displayMessage(QString("Edit structure before saving!"));
                return;
            }
            if (m_QeHandler.saveStructure(m_Structures[m_SelectedStructure]))
            {
                m_Structures[m_SelectedStructure]->edited = false;
                displayMessage(QString("Saving Structure successful!\nSavefile is: ") += m_Structures[m_SelectedStructure]->file);
            }
            else
                displayMessage("Saving Structure failed!");
        }
        else  if (item->text() == "Save As")
        {
            if (m_QeHandler.saveStructure(m_Structures[m_SelectedStructure], true))
            {
                m_Structures[m_SelectedStructure]->edited = false;
                displayMessage(QString("Saving Structure successful!\nSavefile is:") + m_Structures[m_SelectedStructure]->file);
            }
            else
                displayMessage("Saving Structure failed!");
        }
        else if (item->text() == "Edit Structure")
        {

            if (m_CreateStructureWindow != nullptr)
            {
                delete m_CreateStructureWindow;
            }
            m_CreateStructureWindow = new CreateStructureWindow(m_Structures[m_SelectedStructure]);
            QObject::connect(m_CreateStructureWindow, SIGNAL(structureCreated(Structure*)), this, SLOT(acceptStructure(Structure*)));
            QObject::connect(m_CreateStructureWindow, SIGNAL(destroyStructure()), this, SLOT(deleteNewStructure()));
        }
    }

    else if(item->text()== "Settings")
    {
        //m_Structures[m_SelectedStructure]->calculateIdealPositions;
    }
}

void MainWindow::setPosV1ImageCounter(int counter)
{
    m_Structures[m_SelectedStructure]->v1PosImCount = (unsigned int)counter;
    m_Structures[m_SelectedStructure]->updateImageMats();

}

void MainWindow::setNegV1ImageCounter(int counter)
{
    m_Structures[m_SelectedStructure]->v1NegImCount = (unsigned int)counter;
    m_Structures[m_SelectedStructure]->updateImageMats();

}

void MainWindow::setPosV2ImageCounter(int counter)
{
    m_Structures[m_SelectedStructure]->v2PosImCount = (unsigned int)counter;
    m_Structures[m_SelectedStructure]->updateImageMats();


}

void MainWindow::setNegV2ImageCounter(int counter)
{
    m_Structures[m_SelectedStructure]->v2NegImCount = (unsigned int)counter;
    m_Structures[m_SelectedStructure]->updateImageMats();


}

void MainWindow::setPosV3ImageCounter(int counter)
{
    m_Structures[m_SelectedStructure]->v3PosImCount = (unsigned int) counter;
    m_Structures[m_SelectedStructure]->updateImageMats();


}

void MainWindow::setNegV3ImageCounter(int counter)
{
    m_Structures[m_SelectedStructure]->v3NegImCount = (unsigned int)counter;
    m_Structures[m_SelectedStructure]->updateImageMats();

}

void MainWindow::setScales()
{
    ui.lineEdit->blockSignals(true);
    ui.lineEdit_2->blockSignals(true);
    ui.lineEdit_3->blockSignals(true);
	if (m_SelectedStructure != -1)
	{
		ui.lineEdit->setText(QString::number(m_Structures[m_SelectedStructure]->getAtomScale()));
		ui.lineEdit_2->setText(QString::number(m_Structures[m_SelectedStructure]->getBondScale()));
		ui.lineEdit_3->setText(QString::number(m_Structures[m_SelectedStructure]->getCovaScale()));
	}
	else
	{
		ui.lineEdit->setText("/");
		ui.lineEdit_2->setText("/");
		ui.lineEdit_3->setText("/");
	}
	ui.lineEdit->blockSignals(false);
    ui.lineEdit_2->blockSignals(false);
    ui.lineEdit_3->blockSignals(false);

}

//------------------------STRUCTURE MANIPULATION-------------------------//

void MainWindow::mouseClicked(glm::vec4 mouseRay, glm::vec3 cameraPos,glm::mat4 globalTransMat)
{

    m_SelectedAtom = 100000;
    if (m_SelectedStructure == -1)
    {
        return;
    }
    std::vector<glm::vec3> sphCenters;
    std::vector<float> sphRadii;
    std::vector<unsigned int> sphereNumbers;
    for (unsigned int i=0; i<m_Structures[m_SelectedStructure]->spheres.size();i++)
    {

        sphCenters.push_back(glm::vec3(globalTransMat*glm::vec4(m_Structures[m_SelectedStructure]->spheres[i].center, 1.0f)));
        sphRadii.push_back(m_Structures[m_SelectedStructure]->spheres[i].radius);
        sphereNumbers.push_back(m_Structures[m_SelectedStructure]->spheres[i].index);
        for (unsigned int i1 = 0; i1 < m_Structures[m_SelectedStructure]->imMats.size(); i1++)
        {
            sphCenters.push_back(glm::vec3(globalTransMat * (m_Structures[m_SelectedStructure]->imMats[i1] *  glm::vec4(m_Structures[m_SelectedStructure]->spheres[i].center, 1.0f))));
            sphRadii.push_back(m_Structures[m_SelectedStructure]->spheres[i].radius);
            sphereNumbers.push_back(m_Structures[m_SelectedStructure]->spheres[i].index);
        }
    }
    std::vector<float> distances;
    std::vector<uint> selectedAtoms;
    for (unsigned int i=0;i<sphCenters.size();i++)
    {
        float c = glm::length2(cameraPos - sphCenters[i]) - pow(sphRadii[i], 2);
        float b = glm::dot(glm::vec3(mouseRay),(cameraPos - sphCenters[i]));
        if (pow(b,2)>=c)
        {
            selectedAtoms.push_back(sphereNumbers[i]);
            distances.push_back(glm::distance(cameraPos, sphCenters[i]));

        }
    }
    float bestdist=100000000;
    for (int i = 0;i<distances.size();i++)
    {
        if (distances[i]<bestdist)
        {
            bestdist = distances[i];
            m_SelectedAtom = selectedAtoms[i];
        }
    }

    updateAtomSelection();


}

void MainWindow::updateAtomSelection()
{
    if (m_SelectedAtom!= 100000)
    {
        Particle& selectedAtom = m_Structures[m_SelectedStructure]->getAtoms()[m_SelectedAtom];
        ui.tableWidget->displayAtom(selectedAtom);

    }
    else
    {
        ui.tableWidget->reset();
    }
    ui.treeWidget->deselect();
    ui.openGLWidget->updateSelectedAtom(m_SelectedAtom);
    ui.openGLWidget->setFocus();
}

void MainWindow::atomMoved(glm::vec3 direction)
{
    if (m_SelectedAtom!= 100000)
    {
        direction = 0.05f*direction;
        m_Structures[m_SelectedStructure]->updateAtomCoords(m_SelectedAtom, m_Structures[m_SelectedStructure]->getAtomCoords()[m_SelectedAtom]+(glm::dvec3)direction);
        updateAtomSelection();

        ui.openGLWidget->setFocus();
    }
}

void MainWindow::atomInfoEdited(QTableWidgetItem* item)
{
    float new_coord = item->data(0).toFloat();
    glm::dvec3& old_coords = m_Structures[m_SelectedStructure]->getAtomCoords()[m_SelectedAtom];
    glm::dvec3 new_coords;
    if (item->row() == 3)
    {
        new_coords= glm::dvec3(new_coord, old_coords.y,old_coords.z);
    }
    else if (item->row() == 4)
    {
        new_coords=glm::dvec3(old_coords.x,new_coord, old_coords.z);
    }
    else
    {
        new_coords= glm::dvec3(old_coords.x,old_coords.y,new_coord);
    }
    m_Structures[m_SelectedStructure]->updateAtomCoords(m_SelectedAtom,new_coords);
    Particle& selectedAtom = m_Structures[m_SelectedStructure]->getAtoms()[m_SelectedAtom];
    ui.tableWidget->displayAtom(selectedAtom);
}

void MainWindow::atomScaleChanged(QString text)
{
    m_Structures[m_SelectedStructure]->setAtomScale(text.toFloat());

}

void MainWindow::bondScaleChanged(QString text)
{
    m_Structures[m_SelectedStructure]->setBondScale(text.toFloat());


}

void MainWindow::covaScaleChanged(QString text)
{
    m_Structures[m_SelectedStructure]->setCovaScale(text.toFloat());
    ui.openGLWidget->update();
}

//------------------------STRUCTURE CREATION/DESTRUCTION-------------------------//

void MainWindow::acceptStructure(Structure* structure)
{
    m_CreateStructureWindow->close();
    structure->edited = true;
    if (structure->isnew)
    {
        structure->isnew = false;
        m_Structures.push_back(structure);
        tmp_Structure = nullptr;
        m_SelectedStructure = m_Structures.size() - 1;
        ui.treeWidget->addStructure(m_Structures[m_SelectedStructure]);
        ui.openGLWidget->addStructure(m_Structures[m_SelectedStructure]);
    }
    else
        ui.treeWidget->updateStructure(structure);
    m_SelectedAtom = 100000;
    updateAtomSelection();
    displayStructure();
}

void MainWindow::deleteNewStructure()
{
    m_CreateStructureWindow->close();
    delete tmp_Structure;
    tmp_Structure = nullptr;
}

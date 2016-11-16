#include "createstructurewindow.h"

	
CreateStructureWindow::CreateStructureWindow(Structure* tmp_structure):tmp_Structure(tmp_structure)
{
	ui.setupUi(this);
	QObject::connect(m_AtWindow, SIGNAL(atomSelected(Particle)), this, SLOT(addAtom(Particle)));
	initCell();
	initAtoms();
	ui.lineEdit->blockSignals(true);
	ui.lineEdit->setText(tmp_structure->name);
	ui.lineEdit->blockSignals(false);
	raise();
	show();
}

CreateStructureWindow::~CreateStructureWindow()
{
	
	delete m_AtWindow;
}

void CreateStructureWindow::initCell()
{
	ui.tableWidget_2->blockSignals(true);
	ui.comboBox->blockSignals(true);
	glm::dmat3 coords = tmp_Structure->getCell();
	if (abs(sqrt(3) / 2 * coords[0][0] - coords[1][1]) < 0.01f &   abs(coords[0][0] / 2 + coords[1][0]) < 0.02f)
	{
		m_CellLayout = HEXAGONAL;
		ui.tableWidget_2->item(0, 0)->setText(QString::number(coords[0][0]));
		ui.tableWidget_2->item(2, 2)->setText(QString::number(coords[2][2]));
		ui.comboBox->setCurrentIndex(1);
	}
	else if (abs(coords[1][0] + coords[2][0] + coords[0][1] + coords[0][2] + coords[1][2] + coords[2][1]) < 0.01f)
	{
		if (abs(coords[0][0] - coords[1][1]) < 0.01f & abs(coords[0][0] - coords[2][2]) < 0.01f)
		{
			m_CellLayout = CUBIC;
			ui.tableWidget_2->item(0, 0)->setText(QString::number(coords[0][0]));
			ui.comboBox->setCurrentIndex(3);

		}
		else
		{
			m_CellLayout = RECTANGULAR;
			ui.tableWidget_2->item(0, 0)->setText(QString::number(coords[0][0]));
			ui.tableWidget_2->item(1, 1)->setText(QString::number(coords[1][1]));
			ui.tableWidget_2->item(2, 2)->setText(QString::number(coords[2][2]));
			ui.comboBox->setCurrentIndex(2);
		}
	}
	else
	{
		ui.comboBox->setCurrentIndex(0);
		m_CellLayout = CUSTOM;
		for (uint i = 0 ; i < 3 ; i++)
		{
			for (uint i1 = 0 ; i1<3;i1++)
			{
				ui.tableWidget_2->item(i, i1)->setText(QString::number(coords[i][i1]));
			}
		}
	}
	ui.comboBox->blockSignals(false);
	ui.tableWidget_2->blockSignals(false);
	updateCell(1000,0);
}

void CreateStructureWindow::initAtoms()
{
	ui.tableWidget->blockSignals(true);
	std::vector<Particle> atoms = tmp_Structure->getAtoms();
	for (uint i = 0 ; i<atoms.size();i++)
	{
		ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);
		glm::dvec3 coords = glm::inverse(tmp_Structure->getCell())*atoms[i].coords;
		QTableWidgetItem* symbol = new QTableWidgetItem();
		symbol->setFlags(symbol->flags() ^ Qt::ItemIsSelectable);
		symbol->setFlags(symbol->flags() ^ Qt::ItemIsEditable);
		symbol->setText(QString(atoms[i].getSymbol().c_str()));
		ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 0, symbol);
		for (uint i1 = 1; i1<4;i1++)
		{
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setText(QString::number(coords[i1 - 1]));
			ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, i1, item);
		}
	}
	ui.tableWidget->blockSignals(false);

}

void CreateStructureWindow::updateAtomCoords()
{
	glm::dmat3 cell = tmp_Structure->getCell();
	for (uint i = 0 ; i<tmp_Structure->getAtoms().size();i++)
	{
		glm::dvec3 coords = cell* glm::dvec3(ui.tableWidget->item(i, 1)->text().toDouble(), ui.tableWidget->item(i, 2)->text().toDouble(), ui.tableWidget->item(i, 3)->text().toDouble());
		tmp_Structure->setAtomCoords(i, coords);
	}
}

void CreateStructureWindow::closeEvent(QCloseEvent*)
{
	m_AtWindow->close();
}



void CreateStructureWindow::addAtom(Particle atom)
{
	m_AtWindow->close();
	ui.tableWidget->selectionModel()->reset();

	QTableWidgetItem* symbol = new QTableWidgetItem(atom.getSymbol().c_str());
	symbol->setFlags(symbol->flags() ^ Qt::ItemIsSelectable);
	symbol->setFlags(symbol->flags() ^ Qt::ItemIsEditable);
	QTableWidgetItem* V1 = new QTableWidgetItem("0.0");
	QTableWidgetItem* V2 = new QTableWidgetItem("0.0");
	QTableWidgetItem* V3 = new QTableWidgetItem("0.0");
	ui.tableWidget->blockSignals(true);
	ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);
	ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 0, symbol);
	ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 1, V1);
	ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 2, V2);
	ui.tableWidget->setItem(ui.tableWidget->rowCount() - 1, 3, V3);
	ui.tableWidget->blockSignals(false);
	tmp_Structure->addAtom(atom);
}


void CreateStructureWindow::plusButtonClicked()
{
	
	m_AtWindow->init();
	m_AtWindow->show();
	m_AtWindow->raise();
	m_AtWindow->setFocus();

}

void CreateStructureWindow::minButtonClicked()
{

	ui.tableWidget->removeRow(ui.tableWidget->currentRow());
	tmp_Structure->removeAtom(ui.tableWidget->currentRow()+1);
}

void CreateStructureWindow::createButtonClicked()
{
	if (!tmp_Structure->properties.isnew)
		tmp_Structure->resetBufs3D();
	tmp_Structure->create();
	
	emit structureCreated(tmp_Structure);
}

void CreateStructureWindow::editAtom(QTableWidgetItem* item)
{
}

void CreateStructureWindow::editName(QString name)
{
	tmp_Structure->name = name;
}

void CreateStructureWindow::editCoord(QTableWidgetItem* item)
{
    if (item->text().toDouble()<1.0f)
    {
        uint index1 = item->row() ;
        glm::dvec3 coords = (tmp_Structure->getCell())*glm::dvec3(ui.tableWidget->item(item->row(), 1)->text().toDouble(), ui.tableWidget->item(item->row(), 2)->text().toDouble(), ui.tableWidget->item(item->row(), 3)->text().toDouble());
        tmp_Structure->setAtomCoords(index1, coords);
    }
    else
    {
       ui.tableWidget->blockSignals(true);
       item->setText( QString::number((glm::inverse(tmp_Structure->getCell())*(tmp_Structure->getAtomCoords())[item->row()])[item->column()-1]));
       ui.tableWidget->blockSignals(false);
    }

}

void CreateStructureWindow::cancelButtonClicked()
{
	emit destroyStructure();
}

void CreateStructureWindow::comboBoxSelection(QString cellLayout)
{
	if (cellLayout == QString("Custom"))
	{
		m_CellLayout = CUSTOM;
		

	}
	else if (cellLayout == QString("Hexagonal"))
	{
		m_CellLayout = HEXAGONAL;

		
		
		
	
	}
	else if (cellLayout == QString("Rectangular"))
	{
		m_CellLayout = RECTANGULAR;

		

	}
	else if (cellLayout == QString("Cubic"))
	{
		m_CellLayout = CUBIC;
		

	}
	updateCell(1,2);

}

void CreateStructureWindow::updateCell(int i , int j )
{
	tmp_Structure->properties.cellEdited = true;
	ui.tableWidget_2->blockSignals(true);
	switch (m_CellLayout)
	{
	case CUSTOM: 
	{
		ui.tableWidget_2->item(0, 0)->setFlags(ui.tableWidget_2->item(0, 0)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 1)->setFlags(ui.tableWidget_2->item(0, 1)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 2)->setFlags(ui.tableWidget_2->item(0, 2)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 0)->setFlags(ui.tableWidget_2->item(1, 0)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 1)->setFlags(ui.tableWidget_2->item(1, 1)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 2)->setFlags(ui.tableWidget_2->item(1, 2)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 0)->setFlags(ui.tableWidget_2->item(2, 0)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 1)->setFlags(ui.tableWidget_2->item(2, 1)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 2)->setFlags(ui.tableWidget_2->item(2, 2)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 0)->setFlags(ui.tableWidget_2->item(0, 0)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 1)->setFlags(ui.tableWidget_2->item(0, 1)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 2)->setFlags(ui.tableWidget_2->item(0, 2)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 0)->setFlags(ui.tableWidget_2->item(1, 0)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 1)->setFlags(ui.tableWidget_2->item(1, 1)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 2)->setFlags(ui.tableWidget_2->item(1, 2)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 0)->setFlags(ui.tableWidget_2->item(2, 0)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 1)->setFlags(ui.tableWidget_2->item(2, 1)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 2)->setFlags(ui.tableWidget_2->item(2, 2)->flags() | Qt::ItemIsSelectable);
		break;
	}
	case HEXAGONAL: 
	{
		ui.tableWidget_2->item(0, 0)->setFlags(ui.tableWidget_2->item(0, 0)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 0)->setFlags(ui.tableWidget_2->item(0, 0)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 1)->setFlags(ui.tableWidget_2->item(0, 1)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 2)->setFlags(ui.tableWidget_2->item(0, 2)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 0)->setFlags(ui.tableWidget_2->item(1, 0)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 1)->setFlags(ui.tableWidget_2->item(1, 1)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 2)->setFlags(ui.tableWidget_2->item(1, 2)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 0)->setFlags(ui.tableWidget_2->item(2, 0)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 1)->setFlags(ui.tableWidget_2->item(2, 1)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 1)->setFlags(ui.tableWidget_2->item(0, 1)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 2)->setFlags(ui.tableWidget_2->item(0, 2)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 0)->setFlags(ui.tableWidget_2->item(1, 0)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 1)->setFlags(ui.tableWidget_2->item(1, 1)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 2)->setFlags(ui.tableWidget_2->item(1, 2)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 0)->setFlags(ui.tableWidget_2->item(2, 0)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 1)->setFlags(ui.tableWidget_2->item(2, 1)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 2)->setFlags(ui.tableWidget_2->item(2, 2)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 2)->setFlags(ui.tableWidget_2->item(2, 2)->flags() | Qt::ItemIsSelectable);
		double latticeParameter = ui.tableWidget_2->item(0, 0)->text().toDouble();
		ui.tableWidget_2->item(0, 1)->setText(QString("0.0"));
		ui.tableWidget_2->item(0, 2)->setText(QString("0.0"));
		ui.tableWidget_2->item(1, 0)->setText(QString::number(-latticeParameter / 2));
		ui.tableWidget_2->item(1, 1)->setText(QString::number(sqrt(3)*latticeParameter / 2));
		ui.tableWidget_2->item(1, 2)->setText(QString("0.0"));
		ui.tableWidget_2->item(2, 0)->setText(QString("0.0"));
		ui.tableWidget_2->item(2, 1)->setText(QString("0.0"));
		break;
	}
	case RECTANGULAR:
	{
		ui.tableWidget_2->item(0, 0)->setFlags(ui.tableWidget_2->item(0, 0)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 0)->setFlags(ui.tableWidget_2->item(0, 0)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 1)->setFlags(ui.tableWidget_2->item(0, 1)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 2)->setFlags(ui.tableWidget_2->item(0, 2)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 0)->setFlags(ui.tableWidget_2->item(1, 0)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 1)->setFlags(ui.tableWidget_2->item(1, 1)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 2)->setFlags(ui.tableWidget_2->item(1, 2)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 0)->setFlags(ui.tableWidget_2->item(2, 0)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 1)->setFlags(ui.tableWidget_2->item(2, 1)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 2)->setFlags(ui.tableWidget_2->item(2, 2)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 1)->setFlags(ui.tableWidget_2->item(0, 1)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 2)->setFlags(ui.tableWidget_2->item(0, 2)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 0)->setFlags(ui.tableWidget_2->item(1, 0)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 1)->setFlags(ui.tableWidget_2->item(1, 1)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 2)->setFlags(ui.tableWidget_2->item(1, 2)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 0)->setFlags(ui.tableWidget_2->item(2, 0)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 1)->setFlags(ui.tableWidget_2->item(2, 1)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 2)->setFlags(ui.tableWidget_2->item(2, 2)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 1)->setText(QString("0.0"));
		ui.tableWidget_2->item(0, 2)->setText(QString("0.0"));
		ui.tableWidget_2->item(1, 0)->setText(QString("0.0"));
		ui.tableWidget_2->item(1, 2)->setText(QString("0.0"));
		ui.tableWidget_2->item(2, 0)->setText(QString("0.0"));
		ui.tableWidget_2->item(2, 1)->setText(QString("0.0"));
		break;
	}
	case CUBIC:
	{
		ui.tableWidget_2->item(0, 0)->setFlags(ui.tableWidget_2->item(0, 0)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 1)->setFlags(ui.tableWidget_2->item(0, 1)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 2)->setFlags(ui.tableWidget_2->item(0, 2)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 0)->setFlags(ui.tableWidget_2->item(1, 0)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 1)->setFlags(ui.tableWidget_2->item(1, 1)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(1, 2)->setFlags(ui.tableWidget_2->item(1, 2)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 0)->setFlags(ui.tableWidget_2->item(2, 0)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 1)->setFlags(ui.tableWidget_2->item(2, 1)->flags() ^ Qt::ItemIsEditable);
		ui.tableWidget_2->item(2, 2)->setFlags(ui.tableWidget_2->item(2, 2)->flags() | Qt::ItemIsEditable);
		ui.tableWidget_2->item(0, 0)->setFlags(ui.tableWidget_2->item(0, 0)->flags() | Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 1)->setFlags(ui.tableWidget_2->item(0, 1)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(0, 2)->setFlags(ui.tableWidget_2->item(0, 2)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 0)->setFlags(ui.tableWidget_2->item(1, 0)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 1)->setFlags(ui.tableWidget_2->item(1, 1)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(1, 2)->setFlags(ui.tableWidget_2->item(1, 2)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 0)->setFlags(ui.tableWidget_2->item(2, 0)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 1)->setFlags(ui.tableWidget_2->item(2, 1)->flags() ^ Qt::ItemIsSelectable);
		ui.tableWidget_2->item(2, 2)->setFlags(ui.tableWidget_2->item(2, 2)->flags() | Qt::ItemIsSelectable);
		double latticeParameter = ui.tableWidget_2->item(0, 0)->text().toDouble();
		ui.tableWidget_2->item(0, 1)->setText(QString("0.0"));
		ui.tableWidget_2->item(0, 2)->setText(QString("0.0"));
		ui.tableWidget_2->item(1, 0)->setText(QString("0.0"));
		ui.tableWidget_2->item(1, 1)->setText(QString::number(latticeParameter));
		ui.tableWidget_2->item(1, 2)->setText(QString("0.0"));
		ui.tableWidget_2->item(2, 0)->setText(QString("0.0"));
		ui.tableWidget_2->item(2, 1)->setText(QString("0.0"));
		ui.tableWidget_2->item(2, 2)->setText(QString::number(latticeParameter));
		break;
	}
	}
	ui.tableWidget_2->blockSignals(false);
	for (uint i = 0 ; i<ui.tableWidget_2->rowCount();i++)
	{
		glm::dvec3 coords = glm::dvec3(ui.tableWidget_2->item(i, 0)->text().toDouble(), ui.tableWidget_2->item(i, 1)->text().toDouble(), ui.tableWidget_2->item(i, 2)->text().toDouble());
		tmp_Structure->setCellCoords(i, coords);
	}
	if (i!=1000)
	{
		updateAtomCoords();
	}
}

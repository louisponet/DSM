#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif
#include <QtWidgets/QTreeWidgetItem>
#include "treewidget.h"

TreeWidget::TreeWidget(QWidget* parent)
{

}

TreeWidget::~TreeWidget()
{

}

void TreeWidget::addStructure(Structure* structure)
{
	m_Structures.push_back(structure);
	QTreeWidgetItem* item1 = new QTreeWidgetItem();
#ifdef __APPLE__
    CFURLRef appUrlRef;
    appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),CFSTR("/src/icons"),NULL,NULL);
    CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
    const char* pathString = CFStringGetCStringPtr(filePathRef,kCFStringEncodingUTF8);
#else
    const char* pathString = "src/icons";
#endif
    item1->setIcon(0, QIcon((QString(pathString)+QString("/box.xpm")).toStdString().c_str()));
	item1->setText(0, structure->name);
	for (unsigned int i1 = 0; i1 < structure->getAtoms().size(); i1++)
	{
		QTreeWidgetItem* item2 = new QTreeWidgetItem(item1);
		item2->setText(0, QString(structure->getAtoms()[i1].getSymbol().c_str()));
		item2->setIcon(0, QIcon((QString(pathString)+QString("/element.xpm")).toStdString().c_str()));
		item1->addChild(item2);
	}
#ifdef __APPLE__
    CFRelease(appUrlRef);
    CFRelease(filePathRef);
#endif
	addTopLevelItem(item1);
}

void TreeWidget::removeStructure(Structure* structure)
{
	for (int i =0;i<m_Structures.size();i++)
	{
		if (m_Structures[i]==structure)
		{
            m_Structures.erase(m_Structures.begin()+i);
		}
	}
	QString name(structure->name);
	delete findItems(name, Qt::MatchExactly)[0];
	
}

void TreeWidget::updateStructure(Structure* structure)
{
    std::vector<Particle> atoms = structure->getAtoms();
#ifdef __APPLE__
    CFURLRef appUrlRef;
    appUrlRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),CFSTR("/src/icons"),NULL,NULL);
    CFStringRef filePathRef = CFURLCopyPath(appUrlRef);
    const char* pathString = CFStringGetCStringPtr(filePathRef,kCFStringEncodingUTF8);
#else
    const char* pathString = "/src/icons";
#endif
    for (int i =0;i<m_Structures.size();i++)
    {
        if (m_Structures[i]==structure)
        {
            this->topLevelItem(i)->setText(0,structure->name);
            for (int i1 = 0; i1<this->topLevelItem(i)->childCount();i1++)
            {
                this->topLevelItem(i)->child(i1)->setText(0,QString(atoms[i1].getSymbol().c_str()));
            }
            for (int i1=this->topLevelItem(i)->childCount(); i1<atoms.size();i1++)
            {
                QTreeWidgetItem* item = new QTreeWidgetItem();
                item->setIcon(0, QIcon((QString(pathString)+QString("/element.xpm")).toStdString().c_str()));
                item->setText(0,QString(atoms[i1].getSymbol().c_str()));
                this->topLevelItem(i)->addChild(item);
            }
        }
    }
#ifdef __APPLE__
    CFRelease(appUrlRef);
    CFRelease(filePathRef);
#endif
}

void TreeWidget::deselect()
{
	blockSignals(true);
	selectionModel()->reset();
	blockSignals(false);
}


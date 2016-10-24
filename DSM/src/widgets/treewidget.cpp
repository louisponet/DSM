#include <QTreeWidgetItem>
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
	item1->setIcon(0, QIcon("src/icons/box.xpm"));
	item1->setText(0, structure->name);
	for (unsigned int i1 = 0; i1 < structure->getAtoms().size(); i1++)
	{
		QTreeWidgetItem* item2 = new QTreeWidgetItem(item1);
		item2->setText(0, QString(structure->getAtoms()[i1].getSymbol().c_str()));
		item2->setIcon(0, QIcon("src/icons/element.xpm"));
		item1->addChild(item2);
	}
	addTopLevelItem(item1);
}

void TreeWidget::removeStructure(Structure* structure)
{
	for (int i =0;i<m_Structures.size();i++)
	{
		if (m_Structures[i]==structure)
		{
			std::swap(m_Structures.begin() + i, m_Structures.end());
			m_Structures.pop_back();
		}
	}
	QString name(structure->name);
	delete findItems(name, Qt::MatchExactly)[0];
	
}

void TreeWidget::deselect()
{
	blockSignals(true);
	selectionModel()->reset();
	blockSignals(false);
}


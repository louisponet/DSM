#include "tablewidget.h"

TableWidget::TableWidget(QWidget* parent /* = Q_NULLPTR */)
{
}

TableWidget::~TableWidget()
{

}

void TableWidget::displayAtom(Particle& atom)
{
	
	blockSignals(true);
	item(0, 0)->setText(atom.getName().c_str());
	item(1, 0)->setText(atom.getSymbol().c_str());
	item(2, 0)->setText(QString(std::to_string(atom.getCova()).c_str()));
	item(3, 0)->setText(QString(std::to_string(atom.coords.x).c_str()));
	item(4, 0)->setText(QString(std::to_string(atom.coords.y).c_str()));
	item(5, 0)->setText(QString(std::to_string(atom.coords.z).c_str()));
	blockSignals(false);
}

void TableWidget::reset()
{
	blockSignals(true);
	item(0, 0)->setFlags(item(0, 0)->flags() ^ Qt::ItemIsSelectable);
	item(0, 0)->setFlags(item(0, 0)->flags() ^ Qt::ItemIsEditable);
	item(1, 0)->setFlags(item(1, 0)->flags() ^ Qt::ItemIsSelectable);
	item(1, 0)->setFlags(item(1, 0)->flags() ^ Qt::ItemIsEditable);
	item(2, 0)->setFlags(item(2, 0)->flags() ^ Qt::ItemIsSelectable);
	item(2, 0)->setFlags(item(2, 0)->flags() ^ Qt::ItemIsEditable);
	item(0, 0)->setText("/");
	item(1, 0)->setText("/");
	item(2, 0)->setText("/");
	item(3, 0)->setText("/");
	item(4, 0)->setText("/");
	item(5, 0)->setText("/");
	blockSignals(false);
}
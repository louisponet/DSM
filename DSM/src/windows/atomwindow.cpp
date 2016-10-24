#include "atomwindow.h"

AtomWindow::AtomWindow(QWidget * parent)
{
	ui.setupUi(this);
	init();
}



AtomWindow::~AtomWindow() 
{
	
}

void AtomWindow::updateListView(QString text)
{

	ui.listWidget->clear();
	for (uint i = 0 ; i<elements::ELEMENTS.size();i++)
	{
		if (QString(elements::ELEMENTS[i].Symbol.c_str()).startsWith(text))
		{
			QListWidgetItem* item = new QListWidgetItem(QString(elements::ELEMENTS[i].Symbol.c_str()));
			ui.listWidget->addItem(item);
		}
	}
}

void AtomWindow::atomDoubleClicked(QListWidgetItem* item)
{
	for (uint i = 0; i < elements::ELEMENTS.size(); i++)
	{
		if (elements::ELEMENTS[i].Symbol==item->text().toStdString())
		{
			emit atomSelected(Particle(elements::ELEMENTS[i], glm::vec3(0.0f, 0.0f, 0.0f)));
		}
	}
}

void AtomWindow::init()
{
	ui.lineEdit->clear();
	ui.listWidget->clear();
	for (unsigned int i = 0; i < elements::ELEMENTS.size(); i++)
	{
		QListWidgetItem* item = new QListWidgetItem(QString(elements::ELEMENTS[i].Symbol.c_str()));
		ui.listWidget->addItem(item);
	}
	ui.lineEdit->setFocus();
}

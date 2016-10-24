#pragma once
#ifndef GDISMAINWINDOW_H
#define GDISMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_DSMmainwindow.h"
#include "src/entities/structure.h"
#include "src/graphics/generator.h"
#include "src/graphics/glwidget.h"
#include "src/fileio/qeIO.h"
#include "src/windows/createstructurewindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();


	Structure* tmp_Structure=nullptr;
private:
	Ui::DSMmainwindowClass ui;
	std::vector<Structure*> m_Structures;
	qeRW m_QeHandler;
	CreateStructureWindow* m_CreateStructureWindow=nullptr;
	int m_SelectedStructure = -1;
	unsigned int m_SelectedAtom = 100000;

public slots:
	void openStructure();
	void closeStructure();

	void setPosV1ImageCounter(int counter);
	void setNegV1ImageCounter(int counter);
	void setPosV2ImageCounter(int counter);
	void setNegV2ImageCounter(int counter);
	void setPosV3ImageCounter(int counter);
	void setNegV3ImageCounter(int counter);

	void mouseClicked(glm::vec4 mouseRay, glm::vec3 cameraPos, glm::mat4 globalTransMat);
	void atomMoved(glm::vec3 direction);
	void atomInfoEdited(QTableWidgetItem* item);
	void treewidgetSelection(QTreeWidgetItem* item);

	void menuActionTriggered(QAction*);
	void acceptStructure(Structure* structure);
	void deleteNewStructure();

private:
	void updateAtomSelection();
	void displayStructure();
	void displayMessage(QString message);

signals:
	void atomSelected(Particle atom);

};

#endif // GDISMAINWINDOW_H

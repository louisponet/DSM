#pragma once
#include <QtWidgets/QWidget>
#ifdef __APPLE__
#include "../../ui_createstructurewindow.h"
#else
#include "ui_createstructurewindow.h"
#endif
#include "atomwindow.h"
#include "../entities/structure.h"

class CreateStructureWindow : public QWidget
{
	Q_OBJECT
public:
	explicit CreateStructureWindow(Structure* tmp_Structure);
	~CreateStructureWindow();
private:
	void updateAtomCoords();
	void initCell();
	void initAtoms();

public slots:
	void addAtom(Particle atom);
	

private slots:
	void updateCell(int i, int j);
	void plusButtonClicked();
	void minButtonClicked();
	void createButtonClicked();
	void editAtom(QTableWidgetItem* item);
	void editCoord(QTableWidgetItem* item);
	void editName(QString name);
	void cancelButtonClicked();
	void comboBoxSelection(QString cellLayout);
protected:
	void closeEvent(QCloseEvent*);


public:
	Structure* tmp_Structure;
private:
	enum cell_layout {
		CUSTOM,
		HEXAGONAL,
		RECTANGULAR,
		CUBIC
	};
	cell_layout m_CellLayout;
	Ui::createstructurewindow ui;
	AtomWindow* m_AtWindow =new AtomWindow();
signals:
	void structureCreated(Structure* structure);
	void destroyStructure();
};
#pragma once

#include <QtWidgets/QTreeWidget>

#include "../entities/structure.h"

class TreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	explicit TreeWidget(QWidget* parent = Q_NULLPTR);
	~TreeWidget();
	void addStructure(Structure* structure);
	void removeStructure(Structure* structure);
    void updateStructure(Structure* structure);
	void deselect();

private:
	std::vector<Structure*> m_Structures;
};

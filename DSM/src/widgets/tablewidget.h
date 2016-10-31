#pragma once
#include <QtWidgets/QTableWidget>
#include "../entities/particle.h"

class TableWidget :public QTableWidget
{
	Q_OBJECT
public:
	explicit TableWidget(QWidget* parent = Q_NULLPTR);
	~TableWidget();

	void displayAtom(Particle& atom);
	void reset();
};
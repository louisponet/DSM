#pragma once
#ifndef ATOMWINDOW_HPP
#define ATOMWINDOW_HPP
#include <QtWidgets/QListWidgetItem>
#include <QtCore/QString>
#ifdef __APPLE__
#include "../../ui_atomwindow.h"
#else
#include "ui_atomwindow.h"
#endif
#include "../entities/particle.h"

class AtomWindow : public QWidget {
	Q_OBJECT

public:
	explicit AtomWindow(QWidget * parent=Q_NULLPTR);
	~AtomWindow();
	void init();

private:
	Ui::AtomWindow ui;

private slots:
	void updateListView(QString text);
	void atomDoubleClicked(QListWidgetItem* item);
signals:
	void atomSelected(Particle particle);
};

#endif // ATOMWINDOW_HPP
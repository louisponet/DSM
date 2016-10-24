#pragma once
#ifndef ATOMWINDOW_HPP
#define ATOMWINDOW_HPP
#include <QWidget>
#include <QListWidgetItem>
#include <QString>
#include "ui_atomwindow.h"
#include "../src/entities/particle.h"

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
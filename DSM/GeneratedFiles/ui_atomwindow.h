/********************************************************************************
** Form generated from reading UI file 'atomwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATOMWINDOW_H
#define UI_ATOMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AtomWindow
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QListWidget *listWidget;

    void setupUi(QWidget *AtomWindow)
    {
        if (AtomWindow->objectName().isEmpty())
            AtomWindow->setObjectName(QStringLiteral("AtomWindow"));
        AtomWindow->resize(470, 393);
        label = new QLabel(AtomWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 91, 31));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        lineEdit = new QLineEdit(AtomWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 20, 331, 31));
        lineEdit->setFont(font);
        listWidget = new QListWidget(AtomWindow);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(120, 60, 333, 311));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMinimumSize(QSize(332, 311));
        listWidget->setFocusPolicy(Qt::TabFocus);
        listWidget->setTabKeyNavigation(true);

        retranslateUi(AtomWindow);
        QObject::connect(lineEdit, SIGNAL(textChanged(QString)), AtomWindow, SLOT(updateListView(QString)));
        QObject::connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), AtomWindow, SLOT(atomDoubleClicked(QListWidgetItem*)));

        QMetaObject::connectSlotsByName(AtomWindow);
    } // setupUi

    void retranslateUi(QWidget *AtomWindow)
    {
        AtomWindow->setWindowTitle(QApplication::translate("AtomWindow", "AtomWindow", 0));
        label->setText(QApplication::translate("AtomWindow", "Search:", 0));
    } // retranslateUi

};

namespace Ui {
    class AtomWindow: public Ui_AtomWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATOMWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'createstructurewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATESTRUCTUREWINDOW_H
#define UI_CREATESTRUCTUREWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_createstructurewindow
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidget_2;
    QComboBox *comboBox;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *createstructurewindow)
    {
        if (createstructurewindow->objectName().isEmpty())
            createstructurewindow->setObjectName(QStringLiteral("createstructurewindow"));
        createstructurewindow->resize(698, 770);
        gridLayout = new QGridLayout(createstructurewindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit = new QLineEdit(createstructurewindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(10);
        lineEdit->setFont(font);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(createstructurewindow);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(createstructurewindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        groupBox = new QGroupBox(createstructurewindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(671, 251));
        groupBox->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QFont font1;
        font1.setPointSize(9);
        tableWidget->setFont(font1);
        tableWidget->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 3);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QFont font2;
        font2.setPointSize(15);
        pushButton_2->setFont(font2);

        gridLayout_2->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font2);

        gridLayout_2->addWidget(pushButton, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox, 2, 0, 1, 5);

        groupBox_2 = new QGroupBox(createstructurewindow);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMinimumSize(QSize(672, 251));
        groupBox_2->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableWidget_2 = new QTableWidget(groupBox_2);
        if (tableWidget_2->columnCount() < 3)
            tableWidget_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        if (tableWidget_2->rowCount() < 3)
            tableWidget_2->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_2->setItem(2, 2, __qtablewidgetitem18);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setFont(font1);
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(180);
        tableWidget_2->horizontalHeader()->setStretchLastSection(true);
        tableWidget_2->verticalHeader()->setDefaultSectionSize(45);
        tableWidget_2->verticalHeader()->setMinimumSectionSize(45);
        tableWidget_2->verticalHeader()->setStretchLastSection(true);

        gridLayout_3->addWidget(tableWidget_2, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 5);

        comboBox = new QComboBox(createstructurewindow);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 4, 1, 1);

        pushButton_4 = new QPushButton(createstructurewindow);
        buttonGroup = new QButtonGroup(createstructurewindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pushButton_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setFont(font);

        gridLayout->addWidget(pushButton_4, 3, 1, 1, 1);

        pushButton_5 = new QPushButton(createstructurewindow);
        buttonGroup->addButton(pushButton_5);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setFont(font);

        gridLayout->addWidget(pushButton_5, 3, 2, 1, 1);


        retranslateUi(createstructurewindow);
        QObject::connect(pushButton_5, SIGNAL(clicked()), createstructurewindow, SLOT(cancelButtonClicked()));
        QObject::connect(pushButton, SIGNAL(clicked()), createstructurewindow, SLOT(plusButtonClicked()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), createstructurewindow, SLOT(minButtonClicked()));
        QObject::connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), createstructurewindow, SLOT(editCoord(QTableWidgetItem*)));
        QObject::connect(lineEdit, SIGNAL(textEdited(QString)), createstructurewindow, SLOT(editName(QString)));
        QObject::connect(pushButton_4, SIGNAL(clicked()), createstructurewindow, SLOT(createButtonClicked()));
        QObject::connect(comboBox, SIGNAL(currentIndexChanged(QString)), createstructurewindow, SLOT(comboBoxSelection(QString)));
        QObject::connect(tableWidget_2, SIGNAL(cellChanged(int,int)), createstructurewindow, SLOT(updateCell(int,int)));

        QMetaObject::connectSlotsByName(createstructurewindow);
    } // setupUi

    void retranslateUi(QWidget *createstructurewindow)
    {
        createstructurewindow->setWindowTitle(QApplication::translate("createstructurewindow", "Create Structure", 0));
        label->setText(QApplication::translate("createstructurewindow", "Structure Name:", 0));
        label_2->setText(QApplication::translate("createstructurewindow", "Symmetry", 0));
        groupBox->setTitle(QApplication::translate("createstructurewindow", "Atoms", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("createstructurewindow", "Symbol", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("createstructurewindow", "V1", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("createstructurewindow", "V2", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("createstructurewindow", "V3", 0));
        pushButton_2->setText(QApplication::translate("createstructurewindow", "-", 0));
        pushButton->setText(QApplication::translate("createstructurewindow", "+", 0));
        groupBox_2->setTitle(QApplication::translate("createstructurewindow", "Lattice Parameters", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("createstructurewindow", "X", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("createstructurewindow", "Y", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("createstructurewindow", "Z", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_2->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("createstructurewindow", "V1", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_2->verticalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("createstructurewindow", "V2", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_2->verticalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("createstructurewindow", "V3", 0));

        const bool __sortingEnabled = tableWidget_2->isSortingEnabled();
        tableWidget_2->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_2->item(0, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("createstructurewindow", "1.0", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_2->item(0, 1);
        ___qtablewidgetitem11->setText(QApplication::translate("createstructurewindow", "0.0", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_2->item(0, 2);
        ___qtablewidgetitem12->setText(QApplication::translate("createstructurewindow", "0.0", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_2->item(1, 0);
        ___qtablewidgetitem13->setText(QApplication::translate("createstructurewindow", "0.0", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_2->item(1, 1);
        ___qtablewidgetitem14->setText(QApplication::translate("createstructurewindow", "1.0", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_2->item(1, 2);
        ___qtablewidgetitem15->setText(QApplication::translate("createstructurewindow", "0.0", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_2->item(2, 0);
        ___qtablewidgetitem16->setText(QApplication::translate("createstructurewindow", "0.0", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_2->item(2, 1);
        ___qtablewidgetitem17->setText(QApplication::translate("createstructurewindow", "0.0", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_2->item(2, 2);
        ___qtablewidgetitem18->setText(QApplication::translate("createstructurewindow", "1.0", 0));
        tableWidget_2->setSortingEnabled(__sortingEnabled);

        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("createstructurewindow", "Custom", 0)
         << QApplication::translate("createstructurewindow", "Hexagonal", 0)
         << QApplication::translate("createstructurewindow", "Rectangular", 0)
         << QApplication::translate("createstructurewindow", "Cubic", 0)
        );
        pushButton_4->setText(QApplication::translate("createstructurewindow", "Accept", 0));
        pushButton_5->setText(QApplication::translate("createstructurewindow", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class createstructurewindow: public Ui_createstructurewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATESTRUCTUREWINDOW_H

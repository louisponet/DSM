/********************************************************************************
** Form generated from reading UI file 'DSMmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DSMMAINWINDOW_H
#define UI_DSMMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "../src/graphics/glwidget.h"
#include "../src/widgets/tablewidget.h"
#include "../src/widgets/treewidget.h"

QT_BEGIN_NAMESPACE

class Ui_DSMmainwindowClass
{
public:
    QAction *actionOpen_Structure;
    QAction *actionCreate_new_Structure;
    QAction *actionOpen_File;
    QAction *actionClose_Structure;
    QAction *actionSave_Structure;
    QAction *actionSave_Structure_As;
    QAction *actionEdit_Structure;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    TreeWidget *treeWidget;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox_6;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *tab_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    GLWidget *openGLWidget;
    TableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuOpen_Structure;
    QMenu *menuTools;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *DSMmainwindowClass)
    {
        if (DSMmainwindowClass->objectName().isEmpty())
            DSMmainwindowClass->setObjectName(QStringLiteral("DSMmainwindowClass"));
        DSMmainwindowClass->resize(1657, 1041);
        actionOpen_Structure = new QAction(DSMmainwindowClass);
        actionOpen_Structure->setObjectName(QStringLiteral("actionOpen_Structure"));
        QIcon icon;
        icon.addFile(QStringLiteral("src/icons/folder.xpm"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Structure->setIcon(icon);
        actionCreate_new_Structure = new QAction(DSMmainwindowClass);
        actionCreate_new_Structure->setObjectName(QStringLiteral("actionCreate_new_Structure"));
        actionOpen_File = new QAction(DSMmainwindowClass);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionClose_Structure = new QAction(DSMmainwindowClass);
        actionClose_Structure->setObjectName(QStringLiteral("actionClose_Structure"));
        actionSave_Structure = new QAction(DSMmainwindowClass);
        actionSave_Structure->setObjectName(QStringLiteral("actionSave_Structure"));
        actionSave_Structure_As = new QAction(DSMmainwindowClass);
        actionSave_Structure_As->setObjectName(QStringLiteral("actionSave_Structure_As"));
        actionEdit_Structure = new QAction(DSMmainwindowClass);
        actionEdit_Structure->setObjectName(QStringLiteral("actionEdit_Structure"));
        centralWidget = new QWidget(DSMmainwindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        treeWidget = new TreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(300, 16777215));
        treeWidget->header()->setVisible(false);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(300, 245));
        tabWidget->setMaximumSize(QSize(300, 200));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        label = new QLabel(tab1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 91, 61));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label_2 = new QLabel(tab1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 80, 68, 19));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(tab1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 80, 68, 19));
        label_3->setAlignment(Qt::AlignCenter);
        spinBox = new QSpinBox(tab1);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(130, 110, 45, 25));
        spinBox_2 = new QSpinBox(tab1);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(180, 110, 45, 25));
        spinBox_3 = new QSpinBox(tab1);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(130, 140, 45, 25));
        spinBox_4 = new QSpinBox(tab1);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setGeometry(QRect(180, 140, 45, 25));
        spinBox_5 = new QSpinBox(tab1);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setGeometry(QRect(130, 170, 45, 25));
        spinBox_6 = new QSpinBox(tab1);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));
        spinBox_6->setGeometry(QRect(180, 170, 45, 25));
        label_4 = new QLabel(tab1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 110, 68, 19));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_5 = new QLabel(tab1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 140, 68, 19));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(tab1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(50, 170, 68, 19));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tabWidget->addTab(tab1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        checkBox = new QCheckBox(tab_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 80, 111, 23));
        checkBox->setTristate(false);
        checkBox_2 = new QCheckBox(tab_2);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(10, 110, 111, 23));
        checkBox_2->setTristate(false);
        checkBox_3 = new QCheckBox(tab_2);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(10, 140, 121, 21));
        checkBox_3->setTristate(false);
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 2, 0, 1, 1);

        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(1280, 720));
        openGLWidget->setBaseSize(QSize(0, 0));
        openGLWidget->setFocusPolicy(Qt::StrongFocus);

        gridLayout->addWidget(openGLWidget, 0, 2, 4, 1);

        tableWidget = new TableWidget(centralWidget);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(5, 0, __qtablewidgetitem12);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(300, 280));
        tableWidget->setMaximumSize(QSize(320, 242));
        tableWidget->setLineWidth(1);
        tableWidget->setAlternatingRowColors(false);
        tableWidget->setShowGrid(true);
        tableWidget->setColumnCount(1);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(200);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(40);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableWidget, 1, 0, 1, 1);

        DSMmainwindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DSMmainwindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1657, 31));
        menuOpen_Structure = new QMenu(menuBar);
        menuOpen_Structure->setObjectName(QStringLiteral("menuOpen_Structure"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        DSMmainwindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(DSMmainwindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DSMmainwindowClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(DSMmainwindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DSMmainwindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuOpen_Structure->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuOpen_Structure->addAction(actionOpen_File);
        menuOpen_Structure->addAction(actionSave_Structure);
        menuOpen_Structure->addAction(actionSave_Structure_As);
        menuOpen_Structure->addAction(actionClose_Structure);
        menuOpen_Structure->addSeparator();
        menuTools->addAction(actionCreate_new_Structure);
        menuTools->addAction(actionEdit_Structure);
        mainToolBar->addAction(actionOpen_Structure);

        retranslateUi(DSMmainwindowClass);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), DSMmainwindowClass, SLOT(setNegV1ImageCounter(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), DSMmainwindowClass, SLOT(setPosV1ImageCounter(int)));
        QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), DSMmainwindowClass, SLOT(setNegV2ImageCounter(int)));
        QObject::connect(spinBox_4, SIGNAL(valueChanged(int)), DSMmainwindowClass, SLOT(setPosV2ImageCounter(int)));
        QObject::connect(spinBox_5, SIGNAL(valueChanged(int)), DSMmainwindowClass, SLOT(setNegV3ImageCounter(int)));
        QObject::connect(spinBox_6, SIGNAL(valueChanged(int)), DSMmainwindowClass, SLOT(setPosV3ImageCounter(int)));
        QObject::connect(openGLWidget, SIGNAL(mouseClicked(glm::vec4,glm::vec3,glm::mat4)), DSMmainwindowClass, SLOT(mouseClicked(glm::vec4,glm::vec3,glm::mat4)));
        QObject::connect(openGLWidget, SIGNAL(atomMoved(glm::vec3)), DSMmainwindowClass, SLOT(atomMoved(glm::vec3)));
        QObject::connect(mainToolBar, SIGNAL(actionTriggered(QAction*)), DSMmainwindowClass, SLOT(openStructure()));
        QObject::connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), DSMmainwindowClass, SLOT(atomInfoEdited(QTableWidgetItem*)));
        QObject::connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), DSMmainwindowClass, SLOT(treewidgetSelection(QTreeWidgetItem*)));
        QObject::connect(menuBar, SIGNAL(triggered(QAction*)), DSMmainwindowClass, SLOT(menuActionTriggered(QAction*)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DSMmainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *DSMmainwindowClass)
    {
        DSMmainwindowClass->setWindowTitle(QApplication::translate("DSMmainwindowClass", "gdismainwindow", 0));
        actionOpen_Structure->setText(QApplication::translate("DSMmainwindowClass", "Open Structure", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen_Structure->setToolTip(QApplication::translate("DSMmainwindowClass", "Open Structure", 0));
#endif // QT_NO_TOOLTIP
        actionCreate_new_Structure->setText(QApplication::translate("DSMmainwindowClass", "Create new Structure", 0));
        actionOpen_File->setText(QApplication::translate("DSMmainwindowClass", "Open File", 0));
        actionClose_Structure->setText(QApplication::translate("DSMmainwindowClass", "Close", 0));
        actionSave_Structure->setText(QApplication::translate("DSMmainwindowClass", "Save", 0));
        actionSave_Structure_As->setText(QApplication::translate("DSMmainwindowClass", "Save As", 0));
        actionEdit_Structure->setText(QApplication::translate("DSMmainwindowClass", "Edit Structure", 0));
        label->setText(QApplication::translate("DSMmainwindowClass", "Images:", 0));
        label_2->setText(QApplication::translate("DSMmainwindowClass", "-", 0));
        label_3->setText(QApplication::translate("DSMmainwindowClass", "+", 0));
        label_4->setText(QApplication::translate("DSMmainwindowClass", "v1:", 0));
        label_5->setText(QApplication::translate("DSMmainwindowClass", "v2:", 0));
        label_6->setText(QApplication::translate("DSMmainwindowClass", "v3:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("DSMmainwindowClass", "Images", 0));
        checkBox->setText(QApplication::translate("DSMmainwindowClass", "Hide Cells", 0));
        checkBox_2->setText(QApplication::translate("DSMmainwindowClass", "Hide Cells", 0));
        checkBox_3->setText(QApplication::translate("DSMmainwindowClass", "Hide Cells", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DSMmainwindowClass", "Options", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DSMmainwindowClass", "Selected Atom", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("DSMmainwindowClass", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("DSMmainwindowClass", "Symbol", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("DSMmainwindowClass", "Cova", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("DSMmainwindowClass", "X", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("DSMmainwindowClass", "Y", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("DSMmainwindowClass", "Z", 0));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(0, 0);
        ___qtablewidgetitem7->setText(QApplication::translate("DSMmainwindowClass", "/", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(1, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("DSMmainwindowClass", "/", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(2, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("DSMmainwindowClass", "/", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(3, 0);
        ___qtablewidgetitem10->setText(QApplication::translate("DSMmainwindowClass", "/", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(4, 0);
        ___qtablewidgetitem11->setText(QApplication::translate("DSMmainwindowClass", "/", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(5, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("DSMmainwindowClass", "/", 0));
        tableWidget->setSortingEnabled(__sortingEnabled);

        menuOpen_Structure->setTitle(QApplication::translate("DSMmainwindowClass", "File", 0));
        menuTools->setTitle(QApplication::translate("DSMmainwindowClass", "Tools", 0));
    } // retranslateUi

};

namespace Ui {
    class DSMmainwindowClass: public Ui_DSMmainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DSMMAINWINDOW_H

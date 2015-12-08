/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLineEdit *txt;
    QLineEdit *txtCst;
    QPushButton *selectColor;
    QPushButton *quit;
    QComboBox *comboBox;
    QSlider *slider;
    QLCDNumber *lcd;
    QMenuBar *menuBar;
    QMenu *menuTP2_Interfaces_graphiques;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(300, 350);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 280, 40));
        txt = new QLineEdit(centralWidget);
        txt->setObjectName(QStringLiteral("txt"));
        txt->setGeometry(QRect(50, 70, 200, 30));
        txtCst = new QLineEdit(centralWidget);
        txtCst->setObjectName(QStringLiteral("txtCst"));
        txtCst->setGeometry(QRect(50, 110, 200, 30));
        txtCst->setReadOnly(true);
        selectColor = new QPushButton(centralWidget);
        selectColor->setObjectName(QStringLiteral("selectColor"));
        selectColor->setGeometry(QRect(70, 150, 160, 30));
        quit = new QPushButton(centralWidget);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setGeometry(QRect(100, 300, 80, 30));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(90, 190, 120, 30));
        slider = new QSlider(centralWidget);
        slider->setObjectName(QStringLiteral("slider"));
        slider->setGeometry(QRect(60, 260, 170, 20));
        slider->setOrientation(Qt::Horizontal);
        lcd = new QLCDNumber(centralWidget);
        lcd->setObjectName(QStringLiteral("lcd"));
        lcd->setGeometry(QRect(230, 245, 40, 40));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 300, 25));
        menuTP2_Interfaces_graphiques = new QMenu(menuBar);
        menuTP2_Interfaces_graphiques->setObjectName(QStringLiteral("menuTP2_Interfaces_graphiques"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuTP2_Interfaces_graphiques->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "Widgets, signaux, slots, couleurs, fonts", 0));
        selectColor->setText(QApplication::translate("MainWindow", "Select color", 0));
        quit->setText(QApplication::translate("MainWindow", "Quit", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Red", 0)
         << QApplication::translate("MainWindow", "Green", 0)
         << QApplication::translate("MainWindow", "Blue", 0)
         << QApplication::translate("MainWindow", "Cyan", 0)
         << QApplication::translate("MainWindow", "Magenta", 0)
         << QApplication::translate("MainWindow", "Yellow", 0)
         << QApplication::translate("MainWindow", "Gray", 0)
        );
        menuTP2_Interfaces_graphiques->setTitle(QApplication::translate("MainWindow", "TP2  Interfaces graphiques", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

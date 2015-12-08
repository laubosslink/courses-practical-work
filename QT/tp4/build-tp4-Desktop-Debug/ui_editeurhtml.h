/********************************************************************************
** Form generated from reading UI file 'editeurhtml.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITEURHTML_H
#define UI_EDITEURHTML_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditeurHTML
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EditeurHTML)
    {
        if (EditeurHTML->objectName().isEmpty())
            EditeurHTML->setObjectName(QStringLiteral("EditeurHTML"));
        EditeurHTML->resize(558, 334);
        centralWidget = new QWidget(EditeurHTML);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));

        verticalLayout_3->addWidget(tabWidget);


        verticalLayout_2->addLayout(verticalLayout_3);

        EditeurHTML->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditeurHTML);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 558, 20));
        EditeurHTML->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EditeurHTML);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        EditeurHTML->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EditeurHTML);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        EditeurHTML->setStatusBar(statusBar);

        retranslateUi(EditeurHTML);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(EditeurHTML);
    } // setupUi

    void retranslateUi(QMainWindow *EditeurHTML)
    {
        EditeurHTML->setWindowTitle(QApplication::translate("EditeurHTML", "EditeurHTML", 0));
    } // retranslateUi

};

namespace Ui {
    class EditeurHTML: public Ui_EditeurHTML {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITEURHTML_H

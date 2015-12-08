/********************************************************************************
** Form generated from reading UI file 'calculatrice.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATRICE_H
#define UI_CALCULATRICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calculatrice
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *result;
    QGridLayout *gridLayout;
    QPushButton *pushButton_B;
    QPushButton *pushButton_F;
    QComboBox *selectBase;
    QPushButton *pushButton_9;
    QPushButton *pushButton_equal;
    QPushButton *pushButton_multiply;
    QPushButton *pushButton_3;
    QPushButton *pushButton_E;
    QPushButton *pushButton_less;
    QPushButton *pushButton_0;
    QPushButton *pushButton_coma;
    QPushButton *pushButton_6;
    QPushButton *pushButton_div;
    QPushButton *pushButton_5;
    QPushButton *pushButton_1;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_more;
    QLabel *label_2;
    QPushButton *pushButton_D;
    QPushButton *pushButton_A;
    QPushButton *pushButton_C;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_quit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Calculatrice)
    {
        if (Calculatrice->objectName().isEmpty())
            Calculatrice->setObjectName(QStringLiteral("Calculatrice"));
        Calculatrice->resize(513, 443);
        centralWidget = new QWidget(Calculatrice);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 491, 361));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        result = new QLineEdit(verticalLayoutWidget);
        result->setObjectName(QStringLiteral("result"));

        verticalLayout->addWidget(result);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_B = new QPushButton(verticalLayoutWidget);
        pushButton_B->setObjectName(QStringLiteral("pushButton_B"));
        pushButton_B->setEnabled(false);

        gridLayout->addWidget(pushButton_B, 2, 1, 1, 1);

        pushButton_F = new QPushButton(verticalLayoutWidget);
        pushButton_F->setObjectName(QStringLiteral("pushButton_F"));
        pushButton_F->setEnabled(false);

        gridLayout->addWidget(pushButton_F, 1, 1, 1, 1);

        selectBase = new QComboBox(verticalLayoutWidget);
        selectBase->setObjectName(QStringLiteral("selectBase"));

        gridLayout->addWidget(selectBase, 1, 3, 1, 1);

        pushButton_9 = new QPushButton(verticalLayoutWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 3, 2, 1, 1);

        pushButton_equal = new QPushButton(verticalLayoutWidget);
        pushButton_equal->setObjectName(QStringLiteral("pushButton_equal"));

        gridLayout->addWidget(pushButton_equal, 6, 2, 1, 1);

        pushButton_multiply = new QPushButton(verticalLayoutWidget);
        pushButton_multiply->setObjectName(QStringLiteral("pushButton_multiply"));

        gridLayout->addWidget(pushButton_multiply, 6, 3, 1, 1);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 5, 2, 1, 1);

        pushButton_E = new QPushButton(verticalLayoutWidget);
        pushButton_E->setObjectName(QStringLiteral("pushButton_E"));
        pushButton_E->setEnabled(false);
        pushButton_E->setCheckable(false);

        gridLayout->addWidget(pushButton_E, 1, 0, 1, 1);

        pushButton_less = new QPushButton(verticalLayoutWidget);
        pushButton_less->setObjectName(QStringLiteral("pushButton_less"));

        gridLayout->addWidget(pushButton_less, 4, 3, 1, 1);

        pushButton_0 = new QPushButton(verticalLayoutWidget);
        pushButton_0->setObjectName(QStringLiteral("pushButton_0"));

        gridLayout->addWidget(pushButton_0, 6, 0, 1, 1);

        pushButton_coma = new QPushButton(verticalLayoutWidget);
        pushButton_coma->setObjectName(QStringLiteral("pushButton_coma"));

        gridLayout->addWidget(pushButton_coma, 6, 1, 1, 1);

        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 4, 2, 1, 1);

        pushButton_div = new QPushButton(verticalLayoutWidget);
        pushButton_div->setObjectName(QStringLiteral("pushButton_div"));

        gridLayout->addWidget(pushButton_div, 5, 3, 1, 1);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout->addWidget(pushButton_5, 4, 1, 1, 1);

        pushButton_1 = new QPushButton(verticalLayoutWidget);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));

        gridLayout->addWidget(pushButton_1, 5, 0, 1, 1);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 4, 0, 1, 1);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 5, 1, 1, 1);

        pushButton_7 = new QPushButton(verticalLayoutWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 3, 0, 1, 1);

        pushButton_8 = new QPushButton(verticalLayoutWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout->addWidget(pushButton_8, 3, 1, 1, 1);

        pushButton_more = new QPushButton(verticalLayoutWidget);
        pushButton_more->setObjectName(QStringLiteral("pushButton_more"));

        gridLayout->addWidget(pushButton_more, 3, 3, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        pushButton_D = new QPushButton(verticalLayoutWidget);
        pushButton_D->setObjectName(QStringLiteral("pushButton_D"));
        pushButton_D->setEnabled(false);

        gridLayout->addWidget(pushButton_D, 2, 3, 1, 1);

        pushButton_A = new QPushButton(verticalLayoutWidget);
        pushButton_A->setObjectName(QStringLiteral("pushButton_A"));
        pushButton_A->setEnabled(false);

        gridLayout->addWidget(pushButton_A, 2, 0, 1, 1);

        pushButton_C = new QPushButton(verticalLayoutWidget);
        pushButton_C->setObjectName(QStringLiteral("pushButton_C"));
        pushButton_C->setEnabled(false);

        gridLayout->addWidget(pushButton_C, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        pushButton_clear = new QPushButton(verticalLayoutWidget);
        pushButton_clear->setObjectName(QStringLiteral("pushButton_clear"));

        verticalLayout->addWidget(pushButton_clear);

        pushButton_quit = new QPushButton(verticalLayoutWidget);
        pushButton_quit->setObjectName(QStringLiteral("pushButton_quit"));

        verticalLayout->addWidget(pushButton_quit);

        Calculatrice->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Calculatrice);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 513, 20));
        Calculatrice->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Calculatrice);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Calculatrice->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Calculatrice);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Calculatrice->setStatusBar(statusBar);

        retranslateUi(Calculatrice);

        QMetaObject::connectSlotsByName(Calculatrice);
    } // setupUi

    void retranslateUi(QMainWindow *Calculatrice)
    {
        Calculatrice->setWindowTitle(QApplication::translate("Calculatrice", "Calculatrice", 0));
        pushButton_B->setText(QApplication::translate("Calculatrice", "B", 0));
        pushButton_F->setText(QApplication::translate("Calculatrice", "F", 0));
        selectBase->clear();
        selectBase->insertItems(0, QStringList()
         << QApplication::translate("Calculatrice", "Dec", 0)
         << QApplication::translate("Calculatrice", "Binaire", 0)
         << QApplication::translate("Calculatrice", "Hexa", 0)
        );
        pushButton_9->setText(QApplication::translate("Calculatrice", "9", 0));
        pushButton_equal->setText(QApplication::translate("Calculatrice", "=", 0));
        pushButton_multiply->setText(QApplication::translate("Calculatrice", "*", 0));
        pushButton_3->setText(QApplication::translate("Calculatrice", "3", 0));
        pushButton_E->setText(QApplication::translate("Calculatrice", "E", 0));
        pushButton_less->setText(QApplication::translate("Calculatrice", "-", 0));
        pushButton_0->setText(QApplication::translate("Calculatrice", "0", 0));
        pushButton_coma->setText(QApplication::translate("Calculatrice", ",", 0));
        pushButton_6->setText(QApplication::translate("Calculatrice", "6", 0));
        pushButton_div->setText(QApplication::translate("Calculatrice", "/", 0));
        pushButton_5->setText(QApplication::translate("Calculatrice", "5", 0));
        pushButton_1->setText(QApplication::translate("Calculatrice", "1", 0));
        pushButton_4->setText(QApplication::translate("Calculatrice", "4", 0));
        pushButton_2->setText(QApplication::translate("Calculatrice", "2", 0));
        pushButton_7->setText(QApplication::translate("Calculatrice", "7", 0));
        pushButton_8->setText(QApplication::translate("Calculatrice", "8", 0));
        pushButton_more->setText(QApplication::translate("Calculatrice", "+", 0));
        label_2->setText(QApplication::translate("Calculatrice", "Base", 0));
        pushButton_D->setText(QApplication::translate("Calculatrice", "D", 0));
        pushButton_A->setText(QApplication::translate("Calculatrice", "A", 0));
        pushButton_C->setText(QApplication::translate("Calculatrice", "C", 0));
        pushButton_clear->setText(QApplication::translate("Calculatrice", "Clear", 0));
        pushButton_quit->setText(QApplication::translate("Calculatrice", "Quit", 0));
    } // retranslateUi

};

namespace Ui {
    class Calculatrice: public Ui_Calculatrice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATRICE_H

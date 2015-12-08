/**
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
 * @author Parmentier Laurent <laurent.parmentier@ecole.ensicaen.fr>
 * @author Elhimdi Yasmine <yasmine.elhimdi@ecole.ensicaen.fr>
 */

#include "calculatrice.h"
#include "ui_calculatrice.h"

#include <QShortcut>
#include <QMessageBox>

#include "Controller.h"

Calculatrice::Calculatrice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculatrice)
{
    ui->setupUi(this);

    /**
     * Initialisation
     */
    controller = new Controller();

    ui->result->setReadOnly(true);
    ui->result->setText(controller->getText());

    /**
     * Menu bar
     */
    QMenu *fichier = ui->menuBar->addMenu("&Fichier");
    QMenu *options = ui->menuBar->addMenu("&Options");
    QMenu *aide = ui->menuBar->addMenu("&Aide");

    QAction *baseHexa = new QAction("&Hexa", this);
    QAction *baseDec = new QAction("&Decimal", this);
    QAction *baseBin = new QAction("&Binaire", this);
    options->addAction(baseHexa);
    options->addAction(baseDec);
    options->addAction(baseBin);

    QAction *apropos = new QAction("&A propos", this);
    aide->addAction(apropos);

    /**
     * Les bouttons de la calto
     */
    QButtonGroup *b = new QButtonGroup(this);

    b->addButton(ui->pushButton_0, Controller::Button_0);
    ui->pushButton_0->setShortcut(Qt::Key_0);

    b->addButton(ui->pushButton_1, Controller::Button_1);
    ui->pushButton_1->setShortcut(Qt::Key_1);

    b->addButton(ui->pushButton_2, Controller::Button_2);
    ui->pushButton_2->setShortcut(Qt::Key_2);

    b->addButton(ui->pushButton_3, Controller::Button_3);
    ui->pushButton_3->setShortcut(Qt::Key_3);

    b->addButton(ui->pushButton_4, Controller::Button_4);
    ui->pushButton_4->setShortcut(Qt::Key_4);

    b->addButton(ui->pushButton_5, Controller::Button_5);
    ui->pushButton_5->setShortcut(Qt::Key_5);

    b->addButton(ui->pushButton_6, Controller::Button_6);
   ui->pushButton_6->setShortcut(Qt::Key_6);

    b->addButton(ui->pushButton_7, Controller::Button_7);
    ui->pushButton_7->setShortcut(Qt::Key_7);

    b->addButton(ui->pushButton_8, Controller::Button_8);
    ui->pushButton_8->setShortcut(Qt::Key_8);

    b->addButton(ui->pushButton_9, Controller::Button_9);
    ui->pushButton_9->setShortcut(Qt::Key_9);

    b->addButton(ui->pushButton_A, Controller::Button_A);
    ui->pushButton_A->setShortcut(Qt::Key_A);

    b->addButton(ui->pushButton_B, Controller::Button_B);
    ui->pushButton_B->setShortcut(Qt::Key_B);

    b->addButton(ui->pushButton_C, Controller::Button_C);
    ui->pushButton_C->setShortcut(Qt::Key_C);

    b->addButton(ui->pushButton_D, Controller::Button_D);
    ui->pushButton_D->setShortcut(Qt::Key_D);

    b->addButton(ui->pushButton_E, Controller::Button_E);
    ui->pushButton_E->setShortcut(Qt::Key_E);

    b->addButton(ui->pushButton_F, Controller::Button_F);
    ui->pushButton_F->setShortcut(Qt::Key_F);

    b->addButton(ui->pushButton_more, Controller::Button_Plus);
    ui->pushButton_more->setShortcut(Qt::Key_Plus);

    b->addButton(ui->pushButton_less, Controller::Button_Minus);
    ui->pushButton_less->setShortcut(Qt::Key_Minus);

    b->addButton(ui->pushButton_div, Controller::Button_Divide);
    ui->pushButton_div->setShortcut(Qt::Key_Slash);

    b->addButton(ui->pushButton_multiply, Controller::Button_Multiply);
    ui->pushButton_multiply->setShortcut(Qt::Key_Asterisk);

    b->addButton(ui->pushButton_coma, Controller::Button_Dot);
    ui->pushButton_coma->setShortcut(Qt::Key_Comma);

    b->addButton(ui->pushButton_clear, Controller::Button_Clear);

    b->addButton(ui->pushButton_equal, Controller::Button_Equal);
    ui->pushButton_equal->setShortcut(Qt::Key_Equal);

    /**
     * Connections
     */
    connect(baseHexa, SIGNAL(triggered()), this, SLOT(setHexa()));
    connect(baseDec, SIGNAL(triggered()), this, SLOT(setDec()));
    connect(baseBin, SIGNAL(triggered()), this, SLOT(setBin()));

    connect(apropos, SIGNAL(triggered()), this, SLOT(aPropos()));

    connect(ui->selectBase, SIGNAL(currentTextChanged(QString)), this, SLOT(changeBase(QString)));
    connect(b, SIGNAL(buttonClicked(const int &)), this, SLOT(sendCommand(const int &)));
    connect(ui->pushButton_quit, SIGNAL(clicked()), this, SLOT(close()));

    ui->pushButton_equal->installEventFilter(this);
}

void Calculatrice::setHexa()
{
    ui->selectBase->setCurrentText("Hexa");
    changeBase("Hexa");
}

void Calculatrice::setDec()
{
    ui->selectBase->setCurrentText("Dec");
    changeBase("Dec");
}
void Calculatrice::setBin()
{
    ui->selectBase->setCurrentText("Binaire");
    changeBase("Binaire");
}

bool Calculatrice::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        int key = ((QKeyEvent *)event)->key();

        if (key == Qt::Key_Return || key == Qt::Key_Equal || key == Qt::Key_Enter)
        {
            sendCommand(Controller::Button_Equal);
        }

        return true;
    }

    return false;
}

void Calculatrice::changeBase(QString b)
{

    /**
     * TODO peut être optimisé en parcourant une liste de QButtonGroup pour enable/disable
     */

    if(b.contains("Binaire"))
    {
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->pushButton_9->setEnabled(false);

        ui->pushButton_A->setEnabled(false);
        ui->pushButton_B->setEnabled(false);
        ui->pushButton_C->setEnabled(false);
        ui->pushButton_D->setEnabled(false);
        ui->pushButton_E->setEnabled(false);
        ui->pushButton_F->setEnabled(false);

        ui->pushButton_coma->setEnabled(false);

        controller->setBase(Controller::Bin);
    } else if(b.contains("Hexa"))
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);

        ui->pushButton_A->setEnabled(true);
        ui->pushButton_B->setEnabled(true);
        ui->pushButton_C->setEnabled(true);
        ui->pushButton_D->setEnabled(true);
        ui->pushButton_E->setEnabled(true);
        ui->pushButton_F->setEnabled(true);

        ui->pushButton_coma->setEnabled(false);

        controller->setBase(Controller::Hex);
    } else
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_8->setEnabled(true);
        ui->pushButton_9->setEnabled(true);

        ui->pushButton_A->setEnabled(false);
        ui->pushButton_B->setEnabled(false);
        ui->pushButton_C->setEnabled(false);
        ui->pushButton_D->setEnabled(false);
        ui->pushButton_E->setEnabled(false);
        ui->pushButton_F->setEnabled(false);

        ui->pushButton_coma->setEnabled(true);

        controller->setBase(Controller::Dec);
    }
}

void Calculatrice::sendCommand(const int & i)
{
    Controller::ButtonID id = (Controller::ButtonID) i;

    if(controller->command(id))
    {
        QString base = ui->selectBase->currentText();
        QLineEdit *l = ui->result;

        if(base.contains("Binaire"))
        {
            l->setText(controller->getText() + "b");
        } else if(base.contains("Hexa"))
        {
            l->setText(controller->getText() + "Ch");
        } else  /* DÉCIMAL */
        {
            l->setText(controller->getText());
        }
    }
}

void Calculatrice::aPropos()
{
    QMessageBox::information(this, "A propos", "Calculatrice développé par PARMENTIER Laurent et ELHIMDI Yasmine.");
}

Calculatrice::~Calculatrice()
{
    delete ui;
}

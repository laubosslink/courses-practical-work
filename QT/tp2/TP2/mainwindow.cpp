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
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <QMouseEvent>

#include "mainvalidator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cd = new QColorDialog();

    // signal qui permet de changer la couleur du texte  depuis la boite de ColorDialog
    connect(cd, SIGNAL(colorSelected(QColor)), this, SLOT(on_txtCst_setColor(QColor)));

    // signal qui permet de changer la couleur du texte  depuis la comboBox
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_txtCst_setColor(QString)));

    // signal qui permet le changement du lcd lors du déplacement du slide
    connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(on_lcd_setValue(int)));

    // signal qui permet de quitter
    connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));

    // validation de saisie
    QValidator *validator = new MainValidator(this);
    ui->txt->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete cd;
    delete ui;
}

void MainWindow::on_txt_textChanged(const QString &arg1)
{
    ui->txtCst->setText(arg1.toUpper());
}

void MainWindow::on_txtCst_setColor(const QColor & c)
{
    if(c.magenta() == 255)
    {
        ui->comboBox->setCurrentText(QString("Magenta"));
    } else if(c.yellow() == 255)
    {
        ui->comboBox->setCurrentText(QString("Yellow"));
    } else if(c.cyan() == 255)
    {
        ui->comboBox->setCurrentText(QString("Cyan"));
    } else if(c.green() == 255)
    {
        ui->comboBox->setCurrentText(QString("Green"));
    } else if(c.red() == 255)
    {
        ui->comboBox->setCurrentText(QString("Red"));
    } else if(c.blue() == 255)
    {
        ui->comboBox->setCurrentText(QString("Blue"));
    } else
    {
        ui->comboBox->setCurrentText(QString("Gray"));
    }

    QPalette palette = ui->txtCst->palette();
    palette.setColor(QPalette::Text, c);
    ui->txtCst->setPalette(palette);

}

void MainWindow::on_txtCst_setColor(const QString & c)
{
    QPalette palette = ui->txtCst->palette();

    //palette.setColor(QPalette::Text, QColor::setColorFromString(c));

    if(c == "Cyan")
    {
        palette.setColor(QPalette::Text, Qt::cyan);
    } else if(c == "Yellow")
    {
        palette.setColor(QPalette::Text, Qt::yellow);
    } else if(c == "Magenta")
    {
        palette.setColor(QPalette::Text, Qt::magenta);
    } else if(c == "Green")
    {
        palette.setColor(QPalette::Text, Qt::green);
    } else if(c == "Blue")
    {
        palette.setColor(QPalette::Text, Qt::blue);
    } else if(c == "Red")
    {
        palette.setColor(QPalette::Text, Qt::red);
    } else
    {
        palette.setColor(QPalette::Text, Qt::gray);
    }

    ui->txtCst->setPalette(palette);
}

void MainWindow::on_selectColor_clicked()
{
    // affichage du ColorDialog
    cd->show();
}

void MainWindow::on_lcd_setValue(const int & i)
{
    ui->lcd->display(i);
}


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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QColorDialog>

#include "mainvalidator.h"

namespace Ui {
class MainWindow;
class MainValidator;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_txt_textChanged(const QString &arg1);
    void on_selectColor_clicked();
    void on_txtCst_setColor(const QColor & c);
    void on_lcd_setValue(const int & i);
    void on_txtCst_setColor(const QString & c);
private:
    Ui::MainWindow *ui;
    QColorDialog *cd;
};

#endif // MAINWINDOW_H

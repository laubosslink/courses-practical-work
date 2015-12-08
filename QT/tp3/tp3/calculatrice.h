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

#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QMainWindow>

#include "Controller.h"

#include <QKeyEvent>

namespace Ui {
class Calculatrice;
}

class Calculatrice : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculatrice(QWidget *parent = 0);
    ~Calculatrice();
   bool eventFilter(QObject *target, QEvent *event);
private slots:
    void sendCommand(const int &);
    void changeBase(QString);
    void aPropos();
    void setHexa();
    void setDec();
    void setBin();
private:
    Ui::Calculatrice *ui;

    Controller *controller;
};

#endif // CALCULATRICE_H

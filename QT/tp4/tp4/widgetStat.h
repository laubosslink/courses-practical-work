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
#ifndef WIDGETSTAT_H
#define WIDGETSTAT_H

#include <QLabel>

//#include "widgetDocument.h"

class WidgetStat : public QLabel
{
    Q_OBJECT
public slots:
    void update();
public:
    WidgetStat(QWidget *parent);
//    void setWidgetDocument(WidgetDocument*);
private:
//    WidgetDocument* wd;
};

#endif // WIDGETSTAT_H

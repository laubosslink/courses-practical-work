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
#include "widgetStat.h"

WidgetStat::WidgetStat(QWidget *parent = 0) : QLabel(parent)
{
    setText(tr("hello world"));
}

/*
void WidgetStat::setWidgetDocument(WidgetDocument *doc)
{
    WidgetStat::wd = doc;
}*/

void WidgetStat::update()
{
    //setText(wd->getFilename());
}

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

#ifndef WIDGETVUE_H
#define WIDGETVUE_H

#include <QWidget>
#include <QTextDocument>
#include <QTextEdit>

class WidgetVue : public QTextEdit
{
    Q_OBJECT
private:
    QTextDocument *document;
public slots:
    virtual void update();
public:
    WidgetVue();
    void setDocument(QTextDocument *doc);
};

#endif // WIDGETVUE_H

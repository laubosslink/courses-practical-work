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
#ifndef WIDGETDOCUMENT_H
#define WIDGETDOCUMENT_H

#include <QSplitter>

#include <QVBoxLayout>
#include <QTextEdit>
#include <QTextBrowser>
#include <QLabel>

#include "widgetVue.h"
#include "widgetStat.h"

class WidgetDocument : public QSplitter
{
    Q_OBJECT
private:
    QTextEdit *_editor;
    QWidget *_right_widget;
    QVBoxLayout *_right_box;
    QLabel *_apercu_text;
    WidgetVue *_apercu;

    QString *_fileName;

    WidgetStat *_ws;
private slots:
    void checkTitle(bool);
public:
    WidgetDocument(QWidget *parent, WidgetStat *_ws);
    ~WidgetDocument();

    void copy();
    void paste();
    void cut();
    bool isModified();

    bool filenameExist();
    QString getFilename();
    void setFilename(QString & name);

    void saveFile();
    bool loadFile(const QString &);
};

#endif

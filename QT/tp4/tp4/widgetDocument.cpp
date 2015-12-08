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

#include "widgetDocument.h"

#include <QTextStream>
#include <QFile>
#include <QMessageBox>

#include <QDebug>

WidgetDocument::WidgetDocument(QWidget *parent = 0, WidgetStat *ws = 0) : QSplitter(parent)
{
    WidgetDocument::_ws = ws;

    _editor = new QTextEdit(this);
    _right_widget = new QWidget(this);
    _right_box = new QVBoxLayout(this);
    _apercu_text = new QLabel("Aperçu");

    _apercu = new WidgetVue();
    _apercu->setDocument(_editor->document());

    _fileName = 0;

    this->addWidget(_editor);
    this->addWidget(_right_widget);

    _right_widget->setLayout(_right_box);

    _right_box->addWidget(_apercu_text);
    _right_box->addWidget(_apercu);

    connect(_editor->document(), SIGNAL(contentsChanged()), _apercu, SLOT(update()));
    connect(_editor->document(), SIGNAL(contentsChanged()), ws, SLOT(update()));

    connect(_editor->document(), SIGNAL(modificationChanged(bool)), this, SLOT(checkTitle(bool)));

    setWindowTitle(tr("Nouveau"));
}

void WidgetDocument::checkTitle(bool changed)
{
    if(changed)
    {
        if(_fileName == 0)
        {
            setWindowTitle(windowTitle() + " *");
        } else
        {
            setWindowTitle((*_fileName) + " *");
        }
    } else
    {
        if(_fileName != 0)
        {
            setWindowTitle(*_fileName);
        }
    }
}

void WidgetDocument::copy()
{
    _editor->copy();
}

void WidgetDocument::cut()
{
    _editor->cut();
}

void WidgetDocument::paste()
{
    _editor->paste();
}

bool WidgetDocument::isModified()
{
    return _editor->document()->isModified();
}

bool WidgetDocument::filenameExist()
{
    return WidgetDocument::_fileName != 0;
}

QString WidgetDocument::getFilename()
{
    return *_fileName;
}

void WidgetDocument::setFilename(QString & name)
{
    WidgetDocument::_fileName = new QString(name);
    setWindowTitle(name);
}

void WidgetDocument::saveFile()
{
    QFile f(*_fileName);

    if(!f.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("EditeurHTML"), tr("Impossible de sauvegarder le fichier"));
        return;
    }

    //qDebug() << _editor->document()->isModified();

    QByteArray ba(_editor->toPlainText().toStdString().c_str(), _editor->toPlainText().length());
    f.write(ba);
    f.close();

    _editor->document()->setModified(false);
    setWindowTitle(*_fileName);
}

bool WidgetDocument::loadFile(const QString & filename)
{
    WidgetDocument::_fileName = new QString(filename);

    QFile f(filename);

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "EditeurHTML Probleme", "Impossible d'ouvrir le fichier.");
        return false;
    }

    QTextStream st(&f);

    _editor->setPlainText(st.readAll());

    f.close();

    return true;
}

WidgetDocument::~WidgetDocument()
{
    delete _fileName;
}

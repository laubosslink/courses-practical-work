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
#ifndef MAINVALIDATOR_H
#define MAINVALIDATOR_H

#include <QRegExpValidator>
#include <QValidator>

class MainValidator : public QRegExpValidator
{
    Q_OBJECT
public:
    MainValidator(QObject *parent);
    virtual QValidator::State validate(QString & input, int & pos) const;
};

#endif

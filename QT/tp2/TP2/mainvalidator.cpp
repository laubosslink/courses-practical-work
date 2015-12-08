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
#include "mainvalidator.h"

MainValidator::MainValidator(QObject *parent) : QRegExpValidator(parent)
{
    setRegExp(QRegExp("^[0-9]{1,10}[a-z]$"));
}

QValidator::State MainValidator::validate(QString & input, int & pos) const
{
    if(QRegExpValidator::validate(input, pos) == QValidator::Intermediate)
        return QValidator::Intermediate;

    int sum = 0;

    for(int i=0; i<input.size()-1; i++)
    {
        sum += input.at(i).digitValue();
    }

    sum %= 26;

    if((input.at(input.size()-1).toLatin1() - QChar('a').toLatin1()) != sum)
        return QValidator::Invalid;

    return QRegExpValidator::validate(input, pos);
}

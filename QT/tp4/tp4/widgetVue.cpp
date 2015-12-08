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

WidgetVue::WidgetVue()
{
    document = 0;

    setReadOnly(true);
    setAcceptRichText(true);
}

void WidgetVue::update()
{
    setHtml(document->toPlainText());
}

void WidgetVue::setDocument(QTextDocument *doc)
{
    WidgetVue::document = doc;
}

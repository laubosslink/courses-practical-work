#include "editeurhtml.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditeurHTML w;
    w.show();

    return a.exec();
}

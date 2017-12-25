#include <QApplication>

#include "polylineeditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PolylineEditor editor(a);
    editor.show();

    return a.exec();
}

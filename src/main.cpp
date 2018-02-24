#include <QApplication>

#include "ModelPolylineEditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelPolylineEditor modelPolylineEditor;

    ViewPolylineEditor viewPolylineEditor(&modelPolylineEditor);
    viewPolylineEditor.show();

    return a.exec();
}

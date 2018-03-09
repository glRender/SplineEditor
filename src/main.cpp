#include <QApplication>

#include "ModelSplineEditor.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelSplineEditor modelPolylineEditor;

    ViewSplineEditor viewPolylineEditor(&modelPolylineEditor);
    viewPolylineEditor.show();

    return a.exec();
}

#include <QApplication>

#include "ModelSplineEditor.hpp"
#include "ControllerSplineEditor.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelSplineEditor modelSplineEditor;

    ControllerSplineEditor controllerSplineEditor(&modelSplineEditor);

    ViewSplineEditor viewPolylineEditor(&modelSplineEditor, &controllerSplineEditor);
    viewPolylineEditor.show();

    return a.exec();
}

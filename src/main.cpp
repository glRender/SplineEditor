#include <QApplication>
#include <QVector3D>

#include "ModelSplineEditor.hpp"
#include "ModelSpline.hpp"

#include "ControllerSplineEditor.hpp"

#include "ViewSplineArea.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelSplineEditor modelEditor;
    ModelSpline modelSpline;

    ControllerSpline       controllerSpline      (&modelSpline, &modelEditor);
    ControllerSplineEditor controllerSplineEditor(&modelEditor);

    ViewSplineEditor viewPolylineEditor(&controllerSplineEditor, &controllerSpline);
    viewPolylineEditor.show();

    return a.exec();
}

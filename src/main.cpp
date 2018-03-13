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
    modelSpline.add({1,1,-1});
    modelSpline.add({2,1,2});
    QVector3D startPoint(-1.0, 0.0, -5.0);
    for (int i=0; i<10; i++)
    {
        modelSpline.add(startPoint);
        startPoint += QVector3D(0.2,0.0,0.0);
    }

    ControllerSpline       controllerSpline      (&modelSpline, &modelEditor);
    ControllerSplineEditor controllerSplineEditor(&modelEditor);

//    ViewSplineEditor viewPolylineEditor(&controllerSplineEditor, &controllerSpline);
//    viewPolylineEditor.show();

    return a.exec();
}

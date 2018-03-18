#include <QApplication>
#include <QVector3D>

#include "ModelSplineEditor.hpp"
#include "ModelSpline.hpp"

#include "ViewSplineArea.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelSpline modelSpline;
    ModelSplineEditor modelEditor(&modelSpline);

    ViewSplineEditor viewPolylineEditor(&modelEditor);
    viewPolylineEditor.show();

    return a.exec();
}

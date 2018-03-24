#include <QApplication>
#include <QVector3D>
#include <QDebug>

#include "ModelSplineEditor.hpp"
#include "ModelSpline.hpp"

#include "ViewSplineArea.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelSpline modelSpline;
    ModelSplineEditor modelEditor(&modelSpline);

    QList<ModelKnot*> knots = modelSpline.knotModels();
    qDebug() << knots.size();

    ViewSplineEditor viewPolylineEditor(&modelEditor);
    viewPolylineEditor.show();

    return a.exec();
}

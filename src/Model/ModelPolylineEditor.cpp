#include "ModelPolylineEditor.h"

#include "SplineModel.hpp"

ModelPolylineEditor::ModelPolylineEditor(QObject *parent)
    : QObject(parent)
{
    model = QSharedPointer<SplineModel>::create(this);

//    mainWindow = new MainWindow();
//    mainWindow->setModel(model);

    model->add({1,1,-1});
    model->add({2,1,2});

    QVector3D startPoint(-1.0, 0.0, -5.0);
    for (int i=0; i<10; i++)
    {
        model->add(startPoint);
        startPoint += QVector3D(0.2,0.0,0.0);
    }
}

//void PolylineEditor::show()
//{
//    mainWindow->show();

//}


#ifndef POLYLINEEDITOR_H
#define POLYLINEEDITOR_H

#include <QObject>
#include <QApplication>

#include "ViewPolylineEditor.h"

#include "KnotModel.hpp"
#include "SplineModel.hpp"

class ModelPolylineEditor : public QObject
{
    Q_OBJECT
public:
    explicit ModelPolylineEditor(QObject *parent = 0);
//    void show();
    QSharedPointer<SplineModel> model;

public slots:

private:
};

#endif // POLYLINEEDITOR_H

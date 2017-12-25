#ifndef POLYLINEEDITOR_H
#define POLYLINEEDITOR_H

#include <QObject>
#include <QApplication>

#include "mainwindow.h"
#include "model.h"

#include "knot.h"
#include "utils.h"

class PolylineEditor : public QObject
{
    Q_OBJECT
public:
    explicit PolylineEditor(QApplication & a, QObject *parent = 0);
    void show();
    void exit();
    void addKnot(Vec3 pos);
    void removeKnot(uint knotIndex);
    void moveKnot(uint knotIndex, Vec3 pos);
    void setKnotParam(uint knotIndex, Knot::Param param, float value);
    void selectKnot(uint knotIndex);
    void deselectKnot();

private:
    void controllerFollowsUi();
    void uiFollowsModel();

public slots:

private:
    QApplication & a;
    DataModel * model = nullptr;
    MainWindow * ui = nullptr;

};

#endif // POLYLINEEDITOR_H

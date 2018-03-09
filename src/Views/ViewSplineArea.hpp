#ifndef POLYLINEAREA_H
#define POLYLINEAREA_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QSharedPointer>
#include <QMap>

#include "glRender.h"

#include "ViewKnot.hpp"
#include "ViewSegment.hpp"
#include "ViewSpline.hpp"
#include "ControllerSpline.hpp"

class ModelSpline;
class ModelKnot;

using namespace glRender;

class ViewSplineArea : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit ViewSplineArea(QWidget *parent = 0);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

//    void setModel(QSharedPointer<ModelSpline> model);
    void setController(ControllerSpline * controller);

private:
    void createAndStartDrawUpdater();
    void createAndStartLogicUpdater();

    void addKnot(ControllerKnot * controllerKnot);
    void removeKnot(ControllerKnot * controllerKnot);

    void processModel();

private:
//    QSharedPointer<ModelSpline> m_model;
    ControllerSpline * m_controller;

    Render * render = nullptr;
    Scene * scene = nullptr;
    Camera * camera;
    NodePickerPtr nodePicker;
    ViewSpline * m_spline;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

    QMap<ModelKnot *, ViewKnot *> m_viewByModel;

signals:
    void updated();
};

#endif // POLYLINEAREA_H

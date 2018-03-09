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

#include "ViewSplineMark.hpp"
#include "ViewSplineSegment.hpp"
#include "ViewSpline.hpp"

class ModelSpline;
class ModelKnot;

using namespace glRender;

class ViewPolylineArea : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit ViewPolylineArea(QWidget *parent = 0);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void setModel(QSharedPointer<ModelSpline> model);

private:
    void createAndStartDrawUpdater();
    void createAndStartLogicUpdater();

    void addMark(QSharedPointer<ModelKnot> knot);
    void removeMark(QSharedPointer<ModelKnot> knot);

    void processModel();

private:
    QSharedPointer<ModelSpline> m_model;
    Render * render = nullptr;
    Scene * scene = nullptr;
    Camera * camera;
    NodePickerPtr nodePicker;
    ViewSpline * m_spline;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

    QMap<QSharedPointer<ModelKnot>, ViewSplineMark *> m_markByKnot;

signals:
    void updated();
};

#endif // POLYLINEAREA_H

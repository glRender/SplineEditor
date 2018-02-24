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

#include "SplineMarkView.hpp"
#include "SplineSegmentView.hpp"
#include "SplineView.hpp"

class SplineModel;
class KnotModel;

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

    void setModel(QSharedPointer<SplineModel> model);

private:
    void createAndStartDrawUpdater();
    void createAndStartLogicUpdater();

    void addMark(QSharedPointer<KnotModel> knot);
    void removeMark(QSharedPointer<KnotModel> knot);

    void processModel();

private:
    QSharedPointer<SplineModel> m_model;
    Render * render = nullptr;
    Scene * scene = nullptr;
    Camera * camera;
    NodePickerPtr nodePicker;
    SplineView * m_spline;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

    QMap<QSharedPointer<KnotModel>, SplineMarkView *> m_markByKnot;

signals:
    void updated();
};

#endif // POLYLINEAREA_H

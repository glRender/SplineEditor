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

#include "SplineMark.hpp"
#include "SplineSegment.hpp"
#include "Spline.hpp"

class SplineModel;
class KnotModel;

using namespace glRender;

class PolylineArea : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit PolylineArea(QWidget *parent = 0);

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

    void addMark(QVector3D position);
    void addMark(QSharedPointer<KnotModel> knot);

    void removeMark(QSharedPointer<KnotModel> knot);

    void processModel();

private:
    QSharedPointer<SplineModel> m_model;
    Render * render = nullptr;
    Scene * scene = nullptr;
    Camera * camera;
    NodePickerPtr nodePicker;
    Spline * spline0;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

    QMap<QSharedPointer<KnotModel>, SplineMark *> m_markByKnot;

signals:
    void updated();
};

#endif // POLYLINEAREA_H

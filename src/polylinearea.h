#ifndef POLYLINEAREA_H
#define POLYLINEAREA_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QOpenGLWidget>

#include "glRender.h"

using namespace glRender;

class PolylineArea : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit PolylineArea(QWidget *parent = 0);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void createAndStartDrawUpdater();
    void createAndStartLogicUpdater();

private:
    Render * render = nullptr;
    Scene * scene = nullptr;
    Camera * camera;
    NodePicker * nodePicker = nullptr;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

signals:
    void updated();
};

#endif // POLYLINEAREA_H

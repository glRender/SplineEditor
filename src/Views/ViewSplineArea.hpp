#pragma once

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QMap>

#include "glRender.h"

class ModelSplineEditor;
class ViewSpline;

using namespace glRender;

class GLContextKeeper
{
public:
    GLContextKeeper(QOpenGLWidget * widget)
        : m_widget(widget)
    {
        assert(m_widget);
        m_widget->makeCurrent();
    }

    ~GLContextKeeper()
    {
        assert(m_widget);
        m_widget->doneCurrent();
    }

private:
    QOpenGLWidget * m_widget = nullptr;
};

class ViewSplineArea : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit ViewSplineArea(QWidget *parent = 0);

    void setModel(ModelSplineEditor * model);

signals:
    void updated();

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    void createAndStartDrawUpdater();
    void createAndStartLogicUpdater();

    void processModel();

private:
    ModelSplineEditor * m_modelSplineEditor = nullptr;

    Render * render = nullptr;
    Scene * m_scene = nullptr;
    Camera * camera = nullptr;
    NodePickerPtr nodePicker = nullptr;
    ViewSpline * m_viewSpline = nullptr;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

    std::list<std::pair<const char *, std::map<ShaderType, const char *>>> shadersPathes;

};

#pragma once

#include <QMainWindow>
#include <QSharedPointer>

#include "ModelKnot.hpp"

class ModelSplineEditor;
class ControllerSplineEditor;
class ControllerSpline;

namespace Ui {
class ViewSplineEditor;
}

class ModelSpline;

class ViewSplineEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewSplineEditor(ControllerSplineEditor * controllerSplineEditor, ControllerSpline * controllerSpline, QWidget *parent = 0);
    ~ViewSplineEditor();

private:
    Ui::ViewSplineEditor * ui;
    ModelSplineEditor * m_model;
    ControllerSplineEditor * m_controllerSplineEditor;
    ControllerSpline * m_controllerSpline;

};

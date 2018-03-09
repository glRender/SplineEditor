#pragma once

#include <QMainWindow>
#include <QSharedPointer>

#include "ModelKnot.hpp"

class ModelSplineEditor;
class ControllerSplineEditor;

namespace Ui {
class ViewSplineEditor;
}

class ModelSpline;

class ViewSplineEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewSplineEditor(ModelSplineEditor * model, ControllerSplineEditor * controller, QWidget *parent = 0);
    ~ViewSplineEditor();

private:
    Ui::ViewSplineEditor * ui;
    ModelSplineEditor * m_model;
    ControllerSplineEditor * m_controller;
};

#pragma once

#include <QMainWindow>
#include <QSharedPointer>

#include "ModelKnot.hpp"

class ModelSplineEditor;

namespace Ui {
class MainWindow;
}

class ModelSpline;

class ViewSplineEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewSplineEditor(ModelSplineEditor * model, QWidget *parent = 0);
    ~ViewSplineEditor();

private:
    Ui::MainWindow * ui;
    ModelSplineEditor * m_model;
};

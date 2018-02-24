#pragma once

#include <QMainWindow>
#include <QSharedPointer>

#include "KnotModel.hpp"

class ModelPolylineEditor;

namespace Ui {
class MainWindow;
}

class SplineModel;

class ViewPolylineEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewPolylineEditor(ModelPolylineEditor * model, QWidget *parent = 0);
    ~ViewPolylineEditor();

private:
    Ui::MainWindow * ui;
    ModelPolylineEditor * m_model;
};

#pragma once

#include <QWidget>
#include <QDebug>

namespace Ui {
class KnotParamsWidget;
}

class ModelSplineEditor;
class ModelKnot;

class KnotParamsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KnotParamsWidget(QWidget *parent = 0);
    ~KnotParamsWidget();

    void readKnotPosition(const ModelKnot *);
    void readKnotParams(const ModelKnot *);

    void setModel(ModelSplineEditor *);

private:
    Ui::KnotParamsWidget *ui;

    ModelSplineEditor * m_modelSplineEditor = nullptr;

    ModelKnot * m_selectedModelKnot = nullptr;

};

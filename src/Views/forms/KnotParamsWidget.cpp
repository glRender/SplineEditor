#include "KnotParamsWidget.h"
#include "ui_KnotParamsWidget.h"

#include <QVector3D>

#include "ModelSplineEditor.hpp"

KnotParamsWidget::KnotParamsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KnotParamsWidget)
{
    ui->setupUi(this);
}

KnotParamsWidget::~KnotParamsWidget()
{
    delete ui;
}

void KnotParamsWidget::readKnotPosition(const ModelKnot * knot)
{
    assert(knot);
    ui->xDoubleSpinBox->setValue(knot->position().x());
    ui->yDoubleSpinBox->setValue(knot->position().y());
    ui->zDoubleSpinBox->setValue(knot->position().z());
    ui->radiusDoubleSpinBox->setValue(knot->param(ModelKnot::Param::Radius));
}

void KnotParamsWidget::setModel(ModelSplineEditor * model)
{
    assert(model);
    m_modelSplineEditor = model;

    connect(m_modelSplineEditor->modelSpline(), &ModelSpline::loseSelection, this, [this](ModelKnot * knot) {
        disconnect(knot, &ModelKnot::positionChanged, this, &KnotParamsWidget::readKnotPosition);
        setEnabled(false);
    });

    connect(m_modelSplineEditor->modelSpline(), &ModelSpline::newSelection, this, [this](ModelKnot * knot) {
        m_selectedModelKnot = knot;
        connect(knot, &ModelKnot::positionChanged, this, &KnotParamsWidget::readKnotPosition);

        readKnotPosition(knot);

        setEnabled(true);

    });

    auto setPosition = [this]() {
        if (m_selectedModelKnot != nullptr)
        {
            m_selectedModelKnot->setPosition(QVector3D(ui->xDoubleSpinBox->value(),
                                                       ui->yDoubleSpinBox->value(),
                                                       ui->zDoubleSpinBox->value()));
        }
    };

    auto setParams = [this]() {
        if (m_selectedModelKnot != nullptr)
        {
            m_selectedModelKnot->setParam(ModelKnot::Param::Radius, ui->radiusDoubleSpinBox->value());
        }
    };

    connect(ui->xDoubleSpinBox,      &QSpinBox::editingFinished, this, setPosition);
    connect(ui->yDoubleSpinBox,      &QSpinBox::editingFinished, this, setPosition);
    connect(ui->zDoubleSpinBox,      &QSpinBox::editingFinished, this, setPosition);
    connect(ui->radiusDoubleSpinBox, &QSpinBox::editingFinished, this, setParams);

}

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
}

void KnotParamsWidget::readKnotParams(const ModelKnot * knot)
{
    assert(knot);
    ui->tensionDoubleSpinBox->setValue(knot->param(ModelKnot::Param::Tension));
    ui->continuityDoubleSpinBox->setValue(knot->param(ModelKnot::Param::Continuity));
    ui->biasDoubleSpinBox->setValue(knot->param(ModelKnot::Param::Bias));
}

void KnotParamsWidget::setModel(ModelSplineEditor * model)
{
    assert(model);
    m_modelSplineEditor = model;

    connect(m_modelSplineEditor->modelSpline(), &ModelSpline::loseSelection, this, [this](ModelKnot * knot) {
        disconnect(knot, &ModelKnot::positionChanged, this, &KnotParamsWidget::readKnotPosition);
        disconnect(knot, &ModelKnot::paramsChanged,   this, &KnotParamsWidget::readKnotParams);
        setEnabled(false);
    });

    connect(m_modelSplineEditor->modelSpline(), &ModelSpline::newSelection, this, [this](ModelKnot * knot) {
        m_selectedModelKnot = knot;
        connect(knot, &ModelKnot::positionChanged, this, &KnotParamsWidget::readKnotPosition);
        connect(knot, &ModelKnot::paramsChanged,   this, &KnotParamsWidget::readKnotParams);

        readKnotPosition(knot);
        readKnotParams(knot);

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
    connect(ui->xDoubleSpinBox,      &QSpinBox::editingFinished, this, setPosition);
    connect(ui->yDoubleSpinBox,      &QSpinBox::editingFinished, this, setPosition);
    connect(ui->zDoubleSpinBox,      &QSpinBox::editingFinished, this, setPosition);

    connect(ui->tensionDoubleSpinBox,    &QSpinBox::editingFinished, this, [this]() {
        if (m_selectedModelKnot != nullptr)
        {
            m_selectedModelKnot->setParam(ModelKnot::Param::Tension,    ui->tensionDoubleSpinBox->value());
        }
    });

    connect(ui->continuityDoubleSpinBox, &QSpinBox::editingFinished, this, [this]() {
        if (m_selectedModelKnot != nullptr)
        {
            m_selectedModelKnot->setParam(ModelKnot::Param::Continuity, ui->continuityDoubleSpinBox->value());
        }
    });

    connect(ui->biasDoubleSpinBox,       &QSpinBox::editingFinished, this, [this]() {
        if (m_selectedModelKnot != nullptr)
        {
            m_selectedModelKnot->setParam(ModelKnot::Param::Bias,       ui->biasDoubleSpinBox->value());
        }
    });

}

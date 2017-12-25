#include "polylineeditor.h"

PolylineEditor::PolylineEditor(QApplication & a, QObject *parent)
    : QObject(parent)
    , a(a)
    , model(new DataModel(this))
    , ui(new MainWindow())
{
    controllerFollowsUi();
    uiFollowsModel();
}

void PolylineEditor::controllerFollowsUi()
{
    connect(ui, &MainWindow::knotAddEffort, this, &PolylineEditor::addKnot);
    connect(ui, &MainWindow::knotRemoveEffort, this, &PolylineEditor::removeKnot);
    connect(ui, &MainWindow::knotPositionChangeEffort, this, &PolylineEditor::moveKnot);
    connect(ui, &MainWindow::knotParamChangeEffort, this, &PolylineEditor::setKnotParam);
    connect(ui, &MainWindow::knotSelectionEffort, this, &PolylineEditor::selectKnot);
    connect(ui, &MainWindow::exitEffort, this, &PolylineEditor::exit);
}

void PolylineEditor::uiFollowsModel()
{
    connect(model, &DataModel::knotAdded, this, [this](uint knotIndex) {
        Knot * knot = model->getKnot(knotIndex);
        ui->addKnot(knot->position());
    });

    connect(model, &DataModel::knotRemoved, this, [this](uint knotIndex) {
        Knot * knot = model->getKnot(knotIndex);
        ui->removeKnot(knot->position());
    });

    connect(model, &DataModel::knotPositionChange, this, [this](uint knotIndex, Vec3 oldPos, Vec3 newPos) {
        ui->moveKnot(knotIndex, newPos);
    });

    connect(model, &DataModel::knotParamChange, this, [this](uint knotIndex, Knot::Param param, float oldVale, float newValue) {
        ui->setKnotParam(knotIndex, param, newValue);
    });
}

void PolylineEditor::addKnot(Vec3 pos)
{
    model->addKnot(pos);
}

void PolylineEditor::removeKnot(uint knotIndex)
{
    model->removeKnot(knotIndex);
}

void PolylineEditor::moveKnot(uint knotIndex, Vec3 pos)
{
    Knot * knot = model->getKnot(knotIndex);
    knot->setPosition(pos);
}

void PolylineEditor::setKnotParam(uint knotIndex, Knot::Param param, float value)
{
    Knot * knot = model->getKnot(knotIndex);
    knot->setParam(param, value);
}

void PolylineEditor::selectKnot(uint knotIndex)
{
    model->selectKnot(knotIndex);
}

void PolylineEditor::deselectKnot()
{
    model->deselectKnot();
}

void PolylineEditor::exit()
{
    a.exit();
}

void PolylineEditor::show()
{
    ui->show();

}


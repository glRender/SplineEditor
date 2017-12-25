#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utils.h"
#include "knot.h"

#include "glRender.h"

using namespace glRender;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addKnot(Vec3 pos);
    void removeKnot(Vec3 pos);
    void moveKnot(uint knotIndex, Vec3 pos);
    void setKnotParam(uint knotIndex, Knot::Param param, float value);
    void selectKnot(uint knotIndex);
    void deselectKnot();

signals:
    void knotAddEffort(Vec3 pos);
    void knotRemoveEffort(uint knotIndex);
    void knotPositionChangeEffort(uint knotIndex, Vec3 oldPos, Vec3 newPos);
    void knotParamChangeEffort(uint knotIndex, Knot::Param parma, float oldVale, float newValue);
    void knotSelectionEffort(uint knotIndex);

    void knotAdded(uint knotIndex);
    void knotRemoved(uint knotIndex);
    void knotPositionChange(uint knotIndex, Vec3 oldPos, Vec3 newPos);
    void knotParamChange(uint knotIndex, Knot::Param parma, float oldVale, float newValue);
    void knotSelected(uint knotIndex);

    void exitEffort();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

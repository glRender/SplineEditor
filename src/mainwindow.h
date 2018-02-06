#pragma once

#include <QMainWindow>
#include <QSharedPointer>

#include "KnotModel.hpp"

namespace Ui {
class MainWindow;
}

class SplineModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setModel(QSharedPointer<SplineModel> model);

private:
    Ui::MainWindow *ui;
    QSharedPointer<SplineModel> m_model;
};

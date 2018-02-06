#ifndef POLYLINEEDITOR_H
#define POLYLINEEDITOR_H

#include <QObject>
#include <QApplication>

#include "mainwindow.h"

#include "KnotModel.hpp"

class PolylineEditor : public QObject
{
    Q_OBJECT
public:
    explicit PolylineEditor(QApplication & qApplication, QObject *parent = 0);
    void show();
    void exit();

public slots:

private:
    QApplication & qApplication;
    QSharedPointer<SplineModel> model;
    MainWindow * mainWindow = nullptr;

};

#endif // POLYLINEEDITOR_H

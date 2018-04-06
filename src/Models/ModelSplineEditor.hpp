#pragma once

#include <QObject>
#include <QApplication>

#include "ViewSplineEditor.hpp"

#include "ModelKnot.hpp"
#include "ModelSpline.hpp"

class ModelSplineEditor : public QObject
{
    Q_OBJECT
public:
    enum class Mode {
        No,
        Selection,
        Removing,
        Addition,
        Moving
    };

    explicit ModelSplineEditor(ModelSpline * modelSpline, QObject *parent = 0);

    void setMode(Mode mode);
    Mode mode() const;

    ModelSpline * modelSpline() const;

private:
    Mode m_mode = Mode::Selection;

    ModelSpline * m_modelSpline;
};

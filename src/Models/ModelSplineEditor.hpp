#ifndef POLYLINEEDITOR_H
#define POLYLINEEDITOR_H

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
        Deletion,
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

#endif // POLYLINEEDITOR_H

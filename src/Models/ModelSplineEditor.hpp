#ifndef POLYLINEEDITOR_H
#define POLYLINEEDITOR_H

#include <QObject>
#include <QApplication>

#include "ViewSplineEditor.hpp"

#include "ModelKnot.hpp"
#include "ModelSpline.hpp"
#include "EditorModeMachine.hpp"

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

    explicit ModelSplineEditor(QObject *parent = 0);

    ModelSpline * modelSpline() const;

    void setMode(EditorModeMachine::Mode mode);
    EditorModeMachine::Mode mode() const;

private:
    EditorModeMachine * m_modelEditorMode;
    ModelSpline * m_modelSpline;
};

#endif // POLYLINEEDITOR_H

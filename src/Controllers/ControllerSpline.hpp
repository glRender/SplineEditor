#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QMap>

#include "ModelKnot.hpp"
#include "ModelSpline.hpp"
#include "ModelSplineEditor.hpp"

class ControllerSpline : public QObject
{
    Q_OBJECT
public:
    ControllerSpline(ModelSpline * modelSpline, ModelSplineEditor * modelEditor, QObject * parent = nullptr)
        : m_modelSpline(modelSpline)
        , m_modelEditor(modelEditor)
    {
        m_modelSpline->add({1,1,-1});
        m_modelSpline->add({2,1,2});
        QVector3D startPoint(-1.0, 0.0, -5.0);
        for (int i=0; i<10; i++)
        {
            m_modelSpline->add(startPoint);
            startPoint += QVector3D(0.2,0.0,0.0);
        }

    }

    void removeKnot(ModelKnot * modelKnot)
    {
        m_modelSpline->remove(modelKnot);
    }

    const ModelSpline * modelSpline() const
    {
        return m_modelSpline;
    }

    const ModelSplineEditor * modelSplineEditor() const
    {
        return m_modelEditor;
    }

private:
    ModelSpline * m_modelSpline;
    ModelSplineEditor * m_modelEditor;
};

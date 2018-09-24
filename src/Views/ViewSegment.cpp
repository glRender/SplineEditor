#include "ViewSegment.hpp"

#include <QDebug>

#include "ModelKnot.hpp"
#include "ViewLine.hpp"

ViewSegment::ViewSegment(ModelKnot * mk0, ModelKnot * mk1, ModelKnot * mk2)
{
    //Q_CHECK_PTR(mk0);
    Q_CHECK_PTR(mk1);
    Q_CHECK_PTR(mk2);

    m_line = new ViewLine(mk1->glRenderVec3Position(),
                          mk2->glRenderVec3Position(),
                          1.0,
                          m_normalColor);

    setFirst(mk0);
    setSecond(mk1);
    setThird(mk2);

    add(m_line);

    qDebug() << Q_FUNC_INFO;
}

ViewSegment::~ViewSegment()
{
    qDebug() << Q_FUNC_INFO;

    QObject::disconnect(m_mk0PositionChangedConnection);
    QObject::disconnect(m_mk1PositionChangedConnection);
    QObject::disconnect(m_mk2PositionChangedConnection);
    Node::remove(m_line);
}

void ViewSegment::setFirst(ModelKnot * modelKnot)
{
    //Q_CHECK_PTR(modelKnot);
    m_mk0 = modelKnot;
    QObject::disconnect(m_mk0PositionChangedConnection);

    if (modelKnot)
    {
        m_mk0PositionChangedConnection = QObject::connect(modelKnot, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
        });
    }

}

void ViewSegment::setSecond(ModelKnot * modelKnot)
{
//    Q_CHECK_PTR(modelKnot);

    m_mk1 = modelKnot;
    QObject::disconnect(m_mk1PositionChangedConnection);

    if (modelKnot)
    {
        m_line->setPointPosition(ViewLine::Points::FirstPoint, modelKnot->glRenderVec3Position());
        m_mk1PositionChangedConnection = QObject::connect(modelKnot, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
            m_line->setPointPosition(ViewLine::Points::FirstPoint, model->glRenderVec3Position());
        });
    }
}

void ViewSegment::setThird(ModelKnot * modelKnot)
{
//    Q_CHECK_PTR(modelKnot);

    m_mk2 = modelKnot;
    QObject::disconnect(m_mk2PositionChangedConnection);

    if (modelKnot)
    {
        m_line->setPointPosition(ViewLine::Points::LastPoint, modelKnot->glRenderVec3Position());
        m_mk2PositionChangedConnection = QObject::connect(modelKnot, &ModelKnot::positionChanged, [this](const ModelKnot * model) {
            m_line->setPointPosition(ViewLine::Points::LastPoint, model->glRenderVec3Position());
        });
    }
}

void ViewSegment::draw(Camera *)
{

}

bool ViewSegment::isCentralKnot(ModelKnot * modelKnot) const
{
    return m_mk1 == modelKnot;
}

bool ViewSegment::isLeftKnot(ModelKnot * modelKnot) const
{
    return m_mk0 == modelKnot;
}

bool ViewSegment::isRigthKnot(ModelKnot * modelKnot) const
{
    return m_mk2 == modelKnot;
}

ModelKnot * ViewSegment::mk0() const
{
    return m_mk0;
}

ModelKnot * ViewSegment::mk1() const
{
    return m_mk1;
}

ModelKnot * ViewSegment::mk2() const
{
    return m_mk2;
}

void ViewSegment::forgetModelKnot(ModelKnot * modelKnot)
{
    Q_CHECK_PTR(modelKnot);

    if (m_mk0 == modelKnot)
    {
        m_mk0 = nullptr;
    }
    else if (m_mk1 == modelKnot)
    {
        m_mk1 = nullptr;
    }
    else if (m_mk2 == modelKnot)
    {
        m_mk2 = nullptr;
    }
}

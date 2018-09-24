#pragma once

#include "glRender.h"

#include <QObject>

#include "ViewKnot.hpp"

class ViewLine;
class ModelKnot;

using namespace glRender;

class ViewSegment : public NodeMixedWith<IDrawable>
{
public:
    ViewSegment(const ModelKnot *, const ModelKnot *, const ModelKnot *);
    ~ViewSegment();

    void draw(Camera *) override;

    void setFirst(const ModelKnot *);
    void setSecond(const ModelKnot *);
    void setThird(const ModelKnot *);

    bool isCentralKnot(ModelKnot *) const;
    bool isLeftKnot(ModelKnot *) const;
    bool isRigthKnot(ModelKnot *) const;

    const ModelKnot * mk0() const;
    const ModelKnot * mk1() const;
    const ModelKnot * mk2() const;

    void forgetModelKnot(ModelKnot *);


private:
    const ModelKnot * m_mk0 = nullptr;
    const ModelKnot * m_mk1 = nullptr;
    const ModelKnot * m_mk2 = nullptr;

    ViewLine * m_line;
    const Vec3 m_normalColor = Vec3(1.0f,0.0f,1.0f);

    QMetaObject::Connection m_mk0PositionChangedConnection;
    QMetaObject::Connection m_mk1PositionChangedConnection;
    QMetaObject::Connection m_mk2PositionChangedConnection;

};

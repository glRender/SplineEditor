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
    ViewSegment(ModelKnot *, ModelKnot *, ModelKnot *, ModelSplineEditor *);
    ~ViewSegment();

    void draw(Camera *) override;

    void setFirst(ModelKnot *);
    void setSecond(ModelKnot *);
    void setThird(ModelKnot *);

    bool isCentralKnot(ModelKnot *) const;
    bool isLeftKnot(ModelKnot *) const;
    bool isRigthKnot(ModelKnot *) const;

    ModelKnot * mk0() const;
    ModelKnot * mk1() const;
    ModelKnot * mk2() const;

    void removeKnotPointer(ModelKnot *);


private:
    ModelKnot * m_mk0 = nullptr;
    ModelKnot * m_mk1 = nullptr;
    ModelKnot * m_mk2 = nullptr;
    ViewLine * m_line;


    QMetaObject::Connection m_mk0PositionChangedConnection;
    QMetaObject::Connection m_mk2PositionChangedConnection;

};

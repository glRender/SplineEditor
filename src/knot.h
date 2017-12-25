#ifndef KNOT_H
#define KNOT_H

#include "utils.h"

#include "glRender.h"

using namespace glRender;

class Knot
{
public:
    enum class Param
    {
        Radius
    };

    Knot();

    void setParam(Knot::Param param, float value);
    void setPosition(Vec3 pos);
    Vec3 position() const;
};

#endif // KNOT_H

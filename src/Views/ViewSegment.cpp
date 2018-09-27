#include "ViewSegment.hpp"

#include <QDebug>

#include "ModelKnot.hpp"
#include "ViewLine.hpp"

ViewSegment::ViewSegment(const ModelKnot * mk0, const ModelKnot * mk1, const ModelKnot * mk2, const ModelKnot * mk3)
{
    Q_CHECK_PTR(mk1);
    Q_CHECK_PTR(mk2);

    QList<Vec3> points;
    Vec3 r1;
    // Расчитываем производную в первой текущей точке (A)
    {
        float tension    = mk1->param(ModelKnot::Param::Tension);
        float continuity = mk1->param(ModelKnot::Param::Continuity);
        float bias       = mk1->param(ModelKnot::Param::Bias);
        Vec3 g1(0.0f,0.0f,0.0f);
        if (mk0)
        {
            g1 = (mk1->positionGlRenderVec3()-mk0->positionGlRenderVec3()) * (1.0f+bias);
        }
        Vec3 g2 = (mk2->positionGlRenderVec3()-mk1->positionGlRenderVec3()) * (1.0f-bias);
        Vec3 g3 = g2 - g1;

        r1 = (1.0f - tension) * (g1 + 0.5f * g3 * (1.0f + continuity));
    }
    Vec3 r2;
    // Расчитываем производную во второй текущей точке (B)
    {
        float tension    = mk2->param(ModelKnot::Param::Tension);
        float continuity = mk2->param(ModelKnot::Param::Continuity);
        float bias       = mk2->param(ModelKnot::Param::Bias);
        Vec3 g1 = (mk2->positionGlRenderVec3()-mk1->positionGlRenderVec3()) * (1.0f+bias);
        Vec3 g2(0.0f,0.0f,0.0f);
        if (mk3)
        {
            g2 = (mk3->positionGlRenderVec3()-mk2->positionGlRenderVec3()) * (1.0f-bias);
        }

        Vec3 g3 = g2 - g1;

        r2 = (1.0f - tension) * (g1 + 0.5f * g3 * (1.0f - continuity));
    }

    for (uint i=0; i<=m_segmentsNumber; i++)
    {
        float t = (float)i / (float)m_segmentsNumber;
        Vec3 p = interpolate(t, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), r1, r2);
        points.append(p);
    }

    for(uint i=1; i<(uint)points.size(); i++)
    {
        auto line = new ViewLine(points[i-1], points[i], 1.0f, m_normalColor);
        add(line);
        m_lines.append(line);
    }
}

ViewSegment::~ViewSegment()
{
    for (auto line : m_lines)
    {
        Node::remove(line);
        delete line;
    }
}

void ViewSegment::draw(Camera *)
{

}

Vec3 ViewSegment::interpolate(float t, Vec3 p1, Vec3 p2, Vec3 r1, Vec3 r2)
{
    return p1 * (2.0f*t*t*t - 3.0f*t*t + 1.0f) + r1 * (t*t*t - 2.0f*t*t + t) +
            p2 * (-2.0f*t*t*t + 3.0f*t*t) + r2 * (t*t*t - t*t);
}

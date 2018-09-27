#include "ViewSegment.hpp"

#include <QDebug>

#include "ModelKnot.hpp"
#include "ViewLine.hpp"

ViewSegment::ViewSegment(const ModelKnot * mk0, const ModelKnot * mk1, const ModelKnot * mk2, const ModelKnot * mk3)
{
//    Q_CHECK_PTR(mk0);
//    Q_CHECK_PTR(mk1);
//    Q_CHECK_PTR(mk2);
//    Q_CHECK_PTR(mk3);

    QList<Vec3> points;

    if (!mk0 and !mk1 and mk2 and mk3)
    {
        Vec3 r1 = mk3->positionGlRenderVec3()-mk2->positionGlRenderVec3();

        float tension = mk2->param(ModelKnot::Param::Tension);
        Vec3 next_ra = (mk3->positionGlRenderVec3()-mk2->positionGlRenderVec3()) * (1-tension);
        Vec3 r2 = (1.5f * (mk3->positionGlRenderVec3()-mk2->positionGlRenderVec3()) - 0.5f*next_ra) * (1-tension);
        for (uint i=0; i<=m_segmentsNumber; i++)
        {
            float t = (float)i / (float)m_segmentsNumber;
            Vec3 p = interpolate(t, mk2->positionGlRenderVec3(), mk3->positionGlRenderVec3(), r1, r2);
            points.append(p);
        }
    }
    else if (mk0 and mk1 and !mk2 and !mk3)
    {
        float tension = mk0->param(ModelKnot::Param::Tension);
        Vec3 prev_rb = (mk1->positionGlRenderVec3()-mk0->positionGlRenderVec3()) * (1-tension);
        Vec3 r1 = (1.5f * (mk1->positionGlRenderVec3()-mk0->positionGlRenderVec3()) - 0.5f*prev_rb) * (1-tension);

        Vec3 r2 = mk1->positionGlRenderVec3()-mk0->positionGlRenderVec3();

        for (uint i=0; i<=m_segmentsNumber; i++)
        {
            float t = (float)i / (float)m_segmentsNumber;
            Vec3 p = interpolate(t, mk0->positionGlRenderVec3(), mk1->positionGlRenderVec3(), r1, r2);
            points.append(p);
        }
    }
    else if(mk0 and mk1 and mk2 and mk3)
    {
        float tension = mk1->param(ModelKnot::Param::Tension);
        float continuity = mk1->param(ModelKnot::Param::Continuity);
        float bias = mk1->param(ModelKnot::Param::Bias);
        Vec3 r1 = 0.5f*(1.0f-tension)*((1.0f+bias)*(1.0f-continuity)*(mk1->positionGlRenderVec3()-mk0->positionGlRenderVec3())+ (1.0f-bias)*(1.0f+continuity)*(mk2->positionGlRenderVec3()-mk1->positionGlRenderVec3()));

        tension = mk2->param(ModelKnot::Param::Tension);
        continuity = mk2->param(ModelKnot::Param::Continuity);
        bias = mk2->param(ModelKnot::Param::Bias);
        Vec3 r2 = 0.5f*(1.0f-tension)*((1.0f+bias)*(1.0f+continuity)*(mk2->positionGlRenderVec3()-mk1->positionGlRenderVec3())+ (1.0f-bias)*(1.0f-continuity)*(mk3->positionGlRenderVec3()-mk2->positionGlRenderVec3()));

        for (uint i=0; i<=m_segmentsNumber; i++)
        {
            float t = (float)i / (float)m_segmentsNumber;
            Vec3 p = interpolate(t, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), r1, r2);
            points.append(p);
        }
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

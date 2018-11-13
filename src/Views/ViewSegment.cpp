#include "ViewSegment.hpp"

#include <cmath>

#include <QDebug>

#include "ModelKnot.hpp"
#include "ViewLine.hpp"

ViewSegment::ViewSegment(const ModelKnot * mk0, const ModelKnot * mk1, const ModelKnot * mk2, const ModelKnot * mk3)
{
    Q_CHECK_PTR(mk1);
    Q_CHECK_PTR(mk2);

//    qDebug() << "***";
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

//    Vec3 a = 6.0f*mk1->positionGlRenderVec3() + 3.0f*r1 - 6.0f*mk2->positionGlRenderVec3() + 3.0f*r2;
//    Vec3 b = -6.0f*mk1->positionGlRenderVec3() - 4.0f*r1 + 6.0f*mk2->positionGlRenderVec3() - 1.0f*r2;
//    Vec3 c = r1;

//    Vec3 D = b*b - 4.0f * a * c;

////    qDebug() << "D" << "x=" << D.x << "y=" << D.y << "z=" << D.z;

//    float x0 = 0.0f;
//    float x1 = 0.0f;
//    if (D.x >= 0.0f)
//    {
//    x0 = ((float)-b.x + sqrt(D.x)) / 2.0f*a.x;
//    x1 = ((float)-b.x - sqrt(D.x)) / 2.0f*a.x;
//    x0 = std::abs(x0);
//    x1 = std::abs(x1);
//    }
////    qDebug() << "x0,1 " << x0 << x1;

//    float y0 = 0.0f;
//    float y1 = 0.0f;
//    if (D.y >= 0.0f)
//    {
//    y0 = ((float)-b.y + sqrt(D.y)) / 2.0f*a.y;
//    y1 = ((float)-b.y - sqrt(D.y)) / 2.0f*a.y;
//    y0 = std::abs(y0);
//    y1 = std::abs(y1);
//    }
////    qDebug() << "y0,1 " << y0 << y1;

//    float z0 = 0.0f;
//    float z1 = 0.0f;
//    if (D.z >= 0.0f)
//    {
//    z0 = ((float)-b.z + sqrt(D.z)) / 2.0f*a.z;
//    z1 = ((float)-b.z - sqrt(D.z)) / 2.0f*a.z;
//    z0 = std::abs(z0);
//    z1 = std::abs(z1);
//    }
////    qDebug() << "z0,1 " << z0 << z1;

//    float min = 0.01f;
//    float max = 1.0f;

//    float extremum = -1.0f;

//    QList<float> extremums;

//    if (x0 > min and x0 < max)
//    {
//    extremum = std::max(x0, extremum);
//    extremums.append(x0);
//    }
//    if (x1 > min and x1 < max)
//    {
//    extremum = std::max(x1, extremum);
//    extremums.append(x1);
//    }
//    if (y0 > min and y0 < max)
//    {
//    extremum = std::max(y0, extremum);
//    extremums.append(y0);
//    }
//    if (y1 > min and y1 < max)
//    {
//    extremum = std::max(y1, extremum);
//    extremums.append(y1);
//    }
//    if (z0 > min and z0 < max)
//    {
//    extremum = std::max(z0, extremum);
//    extremums.append(z0);
//    }
//    if (z1 > min and z1 < max)
//    {
//    extremum = std::max(z1, extremum);
//    extremums.append(z1);
//    }
////    if (extremum == -1.0f)
////    {
////    extremum = 0.5;
////    extremums.append(extremum);
////    }

//    // points += interpolate(0.5, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), r1, r2);

//    // qDebug() « "{{{";

//    // for (auto extremum : extremums)
//    // {
//    // qDebug() « "*" « extremum « "*";
//    // }

//    // qDebug() « "}}}";

//    std::sort (extremums.begin(), extremums.end(), [](float a, float b) {
//    return a < b;
//    });

    // qDebug() « "{{{";

    // for (auto extremum : extremums)
    // {
    // qDebug() « "*" « extremum « "*";
    // }
    // qDebug() « "}}}";

    QList<Vec3> points;

    using namespace std::placeholders;
    auto f = std::bind(&ViewSegment::interpolate, this, _1, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), r1, r2);

//    points += mk1->positionGlRenderVec3();
//     for(uint i=0; i<(uint)extremums.size(); i+=2)
//     {
//         auto firstExtremum = extremums[i];
//         points += this->approximate(0.0f, firstExtremum, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), f);

//         if (i+1 < extremums.size()-1)
//         {
//             auto secondExtremum = extremums[i+1];
//             points += this->approximate(firstExtremum, secondExtremum, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), f);
//         }

//         if (i+1 == extremums.size()-1)
//         {
//             auto lastExtremum = extremums[i+1];
//             points += this->approximate(lastExtremum, 1.0f, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), f);
//         }

//     }
//    points += mk2->positionGlRenderVec3();

    points += mk1->positionGlRenderVec3();
    points += this->approximate(0.0, 0.33, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), f);
    points += this->approximate(0.33, 0.66, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), f);
    points += this->approximate(0.66, 1.0, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), f);
    points += mk2->positionGlRenderVec3();
//    qDebug() << "points: " << QString::number(points.size());

//    uint m_segmentsNumber = 10;
//    for (uint i=0; i<=m_segmentsNumber; i++)
//    {
//        float t = (float)i / (float)m_segmentsNumber;
//        Vec3 p = interpolate(t, mk1->positionGlRenderVec3(), mk2->positionGlRenderVec3(), r1, r2);
//        points.append(p);
//    }

//    for (auto i : points)
//    {
//        qDebug() << "t" << i.first;
//    }

    for(uint i=1; i<(uint)points.size(); i++)
    {
        auto line = new ViewLine(points[i-1], points[i], 1.0f, m_normalColor);
        add(line);
        m_lines.append(line);
    }
//    qDebug() << "***";

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
            p2 * (-2.0f*t*t*t + 3.0f*t*t)       + r2 * (t*t*t - t*t);
}

QList<Vec3> ViewSegment::approximate(const float & from, const float & to, const Vec3 & p1, const Vec3 & p2, std::function<Vec3(float t)> f)
{
    Q_ASSERT(p1 != p2);
    Q_ASSERT(to > from);

    QList<Vec3> points;
//    if (to <= from)
//    {
//        return points;
//    }

    auto middle = (to - from) * 0.5f;
    auto t = from + middle;
    auto p = f(t);

    float straightDistance = p1.distance(p2);
    float contourDistance = p1.distance(p) + p.distance(p2);

    if (contourDistance <= 0.0f)
    {
        return points;
    }

    float coeff = straightDistance / contourDistance;
//    qDebug() << "coeff: " << coeff;

    if (coeff == coeff and coeff > 0.0f and coeff < 0.99f)
    {
        points += approximate(from, from + middle, p1, p, f);
        points += p;
        points += approximate(from + middle, to, p, p2, f);
    }

    return points;
}

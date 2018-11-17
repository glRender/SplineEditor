#include "ViewSegment.hpp"

#include <cmath>

#include <QDebug>

#include "ModelKnot.hpp"
#include "ModelSpline.hpp"
#include "ViewLine.hpp"

ViewSegment::ViewSegment(const ModelSpline * modelSpline, const ModelKnot * mk0,
                         const ModelKnot * mk1, const ModelKnot * mk2,
                         const ModelKnot * mk3)
{
    Q_CHECK_PTR(mk1);
    Q_CHECK_PTR(mk2);

    auto derivatives = modelSpline->derivative(mk0, mk1, mk2, mk3);

    QList<QVector3D> points;

    using namespace std::placeholders;
    auto f = std::bind(&ModelSpline::interpolate, modelSpline, _1, mk1->position(),
                       mk2->position(), derivatives.first, derivatives.second);

    points += mk1->position();
    points += modelSpline->approximateByLines(0.0, 0.33, mk1->position(),
                                              mk2->position(), f);
    points += modelSpline->approximateByLines(0.33, 0.66, mk1->position(),
                                              mk2->position(), f);
    points += modelSpline->approximateByLines(0.66, 1.0, mk1->position(),
                                              mk2->position(), f);
    points += mk2->position();

    for (uint i = 1; i < (uint) points.size(); i++)
    {
        Vec3 p0(points[i - 1].x(), points[i - 1].y(), points[i - 1].z());
        Vec3 p1(points[i].x(), points[i].y(), points[i].z());

        auto line = new ViewLine(p0, p1, 1.0f, m_normalColor);
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

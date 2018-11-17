#include "ModelSpline.hpp"

#include <float.h>

#include <QDebug>
#include <QElapsedTimer>

double drand(void)
{
    double ret = (double) rand() / ((double) rand() + 0.1);
    return ret - floor(ret);
}

ModelSpline::ModelSpline(QObject * parent)
{
    add({-1, 0, -1});
    add({0, 0, -1});
    add({-0.33, 1.38, -0.95});
    add({2, 1.5, -1});
    add({3, 2.4, -1});
    add({3.5, -0.5, -1});
    add({1.5, -1.5, -1});

    //    srand(time(NULL));

    float a = 3.0f;
    //    float b = 10.0f;
    for (uint i = 0; i < 720; i += 10)
    {
        //        float x = a + (b - a) * (double)rand() / (double)RAND_MAX;
        //        float y = a + (b - a) * (double)rand() / (double)RAND_MAX;
        //        float z = a + (b - a) * (double)rand() / (double)RAND_MAX;
        float x = a * MATH_DEG_TO_RAD(i) * cos(MATH_DEG_TO_RAD(i));
        float y = a * MATH_DEG_TO_RAD(i) * sin(MATH_DEG_TO_RAD(i));
        float z = -1;

        //        qDebug() << "**** " << QString::number(x) << QString::number(y);

        add({x, y, z});
    }
}

bool ModelSpline::availabilityToAdd(QVector3D position) const
{
    return false;
}

bool ModelSpline::add(QVector3D position)
{
    ModelKnot * modelKnot = new ModelKnot();
    modelKnot->setPosition(position);
    modelKnot->setParam(ModelKnot::Param::Continuity, 0.05f);
    modelKnot->setParam(ModelKnot::Param::Bias, 0.7f);
    modelKnot->setParam(ModelKnot::Param::Tension, 0.1f);

    connect(modelKnot, &ModelKnot::selectionChanged,
            [this, modelKnot](bool selected) {
                if (selected and m_selectedKnot != modelKnot)
                {
                    if (m_selectedKnot != nullptr)
                    {
                        m_selectedKnot->setSelected(false);
                    }
                    m_selectedKnot = modelKnot;
                }
                emit selectionChanged(modelKnot, selected);
            });

    m_knots.append(modelKnot);

    emit added(modelKnot);
    return true;
}

QList<ModelKnot *> ModelSpline::knotModels() const
{
    return m_knots;
}

uint ModelSpline::size() const
{
    return m_knots.size();
}

QPair<QVector3D, QVector3D> ModelSpline::derivative(const ModelKnot * mk0, const ModelKnot * mk1, const ModelKnot * mk2, const ModelKnot * mk3) const
{
    // Расчитываем производную в первой текущей точке (A)
    QVector3D r1;
    {
        float tension    = mk1->param(ModelKnot::Param::Tension);
        float continuity = mk1->param(ModelKnot::Param::Continuity);
        float bias       = mk1->param(ModelKnot::Param::Bias);
        QVector3D g1(0.0f, 0.0f, 0.0f);
        if (mk0)
        {
            g1 = (mk1->position() - mk0->position()) * (1.0f + bias);
        }
        QVector3D g2 = (mk2->position() - mk1->position()) * (1.0f - bias);
        QVector3D g3 = g2 - g1;

        r1 = (1.0f - tension) * (g1 + 0.5f * g3 * (1.0f + continuity));
    }
    // Расчитываем производную во второй текущей точке (B)
    QVector3D r2;
    {
        float tension    = mk2->param(ModelKnot::Param::Tension);
        float continuity = mk2->param(ModelKnot::Param::Continuity);
        float bias       = mk2->param(ModelKnot::Param::Bias);
        QVector3D g1     = (mk2->position() - mk1->position()) * (1.0f + bias);
        QVector3D g2(0.0f, 0.0f, 0.0f);
        if (mk3)
        {
            g2 = (mk3->position() - mk2->position()) * (1.0f - bias);
        }

        QVector3D g3 = g2 - g1;

        r2 = (1.0f - tension) * (g1 + 0.5f * g3 * (1.0f - continuity));
    }

    return {r1, r2};
}

QVector3D ModelSpline::interpolate(float t, QVector3D p1, QVector3D p2, QVector3D r1, QVector3D r2) const
{
    return p1 * (2.0f * t * t * t - 3.0f * t * t + 1.0f) + r1 * (t * t * t - 2.0f * t * t + t) + p2 * (-2.0f * t * t * t + 3.0f * t * t) + r2 * (t * t * t - t * t);
}

QList<QVector3D> ModelSpline::approximateByLines(const float & from, const float & to, const QVector3D & p1, const QVector3D & p2, std::function<QVector3D(float)> f) const
{
    Q_ASSERT(p1 != p2);
    Q_ASSERT(to > from);

    QList<QVector3D> points;
    //    if (to <= from)
    //    {
    //        return points;
    //    }

    auto middle = (to - from) * 0.5f;
    auto t      = from + middle;
    auto p      = f(t);

    float straightDistance = p1.distanceToPoint(p2);
    float contourDistance  = p1.distanceToPoint(p) + p.distanceToPoint(p2);

    if (contourDistance <= 0.0f)
    {
        return points;
    }

    float coeff = straightDistance / contourDistance;
    //    qDebug() << "coeff: " << coeff;

    if (coeff == coeff and coeff > 0.0f and coeff < 0.99f)
    {
        points += approximateByLines(from, from + middle, p1, p, f);
        points += p;
        points += approximateByLines(from + middle, to, p, p2, f);
    }

    return points;
}

const ModelKnot * ModelSpline::at(uint index) const
{
    if (index >= 0 and index < (uint) m_knots.size())
    {
        return m_knots[index];
    }
    else
    {
        return nullptr;
    }
}

int ModelSpline::indexOf(const ModelKnot * knot) const
{
    for (int i = 0; i < m_knots.size(); i++)
    {
        if (m_knots[i] == knot)
        {
            return i;
        }
    }
    return -1;
}

bool ModelSpline::remove(ModelKnot * knot)
{
    m_knots.removeOne(knot);
    emit removed(knot);
    delete knot;
    return true;
}

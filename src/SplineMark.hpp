#pragma once

#include "glRender.h"

#include "Line.hpp"

namespace glRender {

class SplineMark : public NodeMixedWith<IDrawable, IIntersectable>
{
public:
    enum class Event
    {
        Change
    };

    SplineMark(Vec3 position)
        : m_aabb(new AABB(Vec3(0,0,0), 0.1))
        , m_color(Vec3(0,1,0))
    {
        std::shared_ptr<Geometry> geometry = GeometryHelper::Box(0.1);

        Textures * textures = new Textures();

        std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::instance().shaderPrograms().get("coloredShP");

        shaderProgram->addAttribute<Vec3>("vertex");

        shaderProgram->addUniform<Mat4>("projection");
        shaderProgram->addUniform<Mat4>("view");
        shaderProgram->addUniform<Mat4>("model");
        shaderProgram->addUniform<Vec3>("color");

        shaderProgram->setUniform<Vec3>("color", m_color);

        m_model = new Model(geometry, textures, shaderProgram);
        m_model->setWireframeMode(true);        
        setOrigin(position);
    }

    ~SplineMark()
    {
        delete m_aabb;
    }

    void addCallbackOn(Event event, std::function<void(void)> callback)
    {

    }

    void draw(Camera * camera) override
    {
        m_model->shaderProgram()->setUniform<Vec3>("color", m_color);
        m_model->setParentsMatrix(globalTransforms());
        m_model->draw(camera);        
    }

    const Model * model() const
    {
        return m_model;
    }

    const IBoundingBox * bb() const
    {
        return m_aabb;
    }

    bool intersects(const RayPtr ray) const override
    {
        return m_aabb->intersects(ray);
    }

    void setOrigin(const Vec3 & origin)
    {
        m_model->setOrigin(origin);
        m_aabb->setOrigin(origin);
    }

    void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) override
    {
        m_isSelected = false;

    }

    void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) override
    {
        changeColor();

        Vec3 n = camera->front();
        Vec3 M1 = camera->position();
        Vec3 M2 = model()->origin();

        float D1 = -(n.x*M1.x + n.y*M1.y + n.z*M1.z);
        float D2 = -(n.x*M2.x + n.y*M2.y + n.z*M2.z);

        float top = fabs(D2-D1);
        float bottom = sqrt( pow(n.x, 2) +
                             pow(n.y, 2) +
                             pow(n.z, 2) );

        float distance = bb()->origin().distance(camera->position());
        distance = top / bottom;

        m_isSelected = true;

        std::cout << "Selected!" << std::endl;
        printf("The distance to plane of camera: %f\n", distance);
        std::cout << "" << std::endl;
        
    }

    void onMouseMove(Vec3 & toPosition) override
    {
        setOrigin(toPosition);

        for (auto i : m_points)
        {
            i.first->setPointPosition(i.second, toPosition);
        }

        printf("New position: %f, %f, %f\n", toPosition.x, toPosition.y, toPosition.z);
        std::cout << "" << std::endl;
        
    }

    void changeColor()
    {
        if (m_color.x == 1 && m_color.y == 0 && m_color.z == 0)
        {
            m_color.set(0,1,0);
        }
        else if (m_color.x == 0 && m_color.y == 1 && m_color.z == 0)
        {
            m_color.set(1,0,0);
        }

    }

    void addLinePoint(Line * line, Line::POINTS point)
    {
      // m_line = line;
      // m_linePoint = point;
        m_points[line] = point;
    }

private:
    std::map<Line *, Line::POINTS> m_points;

    AABB * m_aabb;
    Vec3 m_color;
    Model * m_model;
    bool m_isSelected = false;

};

}
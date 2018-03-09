#include "ViewSplineMark.hpp"

#include "ModelKnot.hpp"

ViewSplineMark::ViewSplineMark(ModelKnot * model)
    : m_model(model)
    , m_aabb(new AABB(Vec3(0,0,0), 0.1))
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

    m_mesh = new Model(geometry, textures, shaderProgram);
    m_mesh->setWireframeMode(true);

    const Vec3 position = {m_model->position().x(), m_model->position().y(), m_model->position().z()};
    setOrigin(position);
}

ViewSplineMark::~ViewSplineMark()
{
    delete m_aabb;
}

void ViewSplineMark::draw(Camera *camera)
{
    m_mesh->shaderProgram()->setUniform<Vec3>("color", m_color);
    m_mesh->setParentsMatrix(globalTransforms());
    m_mesh->draw(camera);
}

const Model *ViewSplineMark::model() const
{
    return m_mesh;
}

const IBoundingBox *ViewSplineMark::bb() const
{
    return m_aabb;
}

bool ViewSplineMark::intersects(const RayPtr ray) const
{
    return m_aabb->intersects(ray);
}

void ViewSplineMark::setOrigin(const Vec3 &origin)
{
    m_mesh->setOrigin(origin);
    m_aabb->setOrigin(origin);
}

void ViewSplineMark::onMouseUp(Vec3 &position, RayPtr ray, Camera *camera)
{
    m_isSelected = false;
//    m_model->onMouseUp();
}

void ViewSplineMark::onMouseDown(Vec3 &position, RayPtr ray, Camera *camera)
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

//    m_model->onMouseDown();
}

void ViewSplineMark::onMouseMove(Vec3 &toPosition)
{
    setOrigin(toPosition);

    for (auto i : m_points)
    {
        i.first->setPointPosition(i.second, toPosition);
    }

    printf("New position: %f, %f, %f\n", toPosition.x, toPosition.y, toPosition.z);
    std::cout << "" << std::endl;

//    m_model->onMouseMove();
}

void ViewSplineMark::changeColor()
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

void ViewSplineMark::addLinePoint(ViewLine *line, ViewLine::POINTS point)
{
    // m_line = line;
    // m_linePoint = point;
    m_points[line] = point;
}

#include "ViewKnot.hpp"

#include "ModelKnot.hpp"
#include "ViewSegment.hpp"

ViewKnot::ViewKnot(ModelKnot * model, std::function<void()> onMouseUp)
    : m_model(model)
    , m_aabb(new AABB(Vec3(0,0,0), 0.1))
    , m_color(Vec3(0,1,0))
    , m_onMouseUpCallback(onMouseUp)
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

ViewKnot::~ViewKnot()
{
    delete m_aabb;
}

void ViewKnot::draw(Camera *camera)
{
    m_mesh->shaderProgram()->setUniform<Vec3>("color", m_color);
    m_mesh->setParentsMatrix(globalTransforms());
    m_mesh->draw(camera);
}

const Model *ViewKnot::mesh() const
{
    return m_mesh;
}

ModelKnot *ViewKnot::model() const
{
    return m_model;
}

const IBoundingBox *ViewKnot::bb() const
{
    return m_aabb;
}

bool ViewKnot::intersects(const RayPtr ray) const
{
    return m_aabb->intersects(ray);
}

void ViewKnot::setOrigin(const Vec3 &origin)
{
    m_mesh->setOrigin(origin);
    m_aabb->setOrigin(origin);
}

void ViewKnot::onMouseUp(Vec3 &position, RayPtr ray, Camera * camera)
{
    m_isSelected = false;
//    m_model->onMouseUp();
    m_onMouseUpCallback();
}

void ViewKnot::onMouseDown(Vec3 &position, RayPtr ray, Camera * camera)
{
    changeColor();

    Vec3 n = camera->front();
    Vec3 M1 = camera->position();
    Vec3 M2 = mesh()->origin();

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

//    m_controller->mouseDown();
}

void ViewKnot::onMouseMove(Vec3 &toPosition)
{
    setOrigin(toPosition);

//    for (auto i : m_pointOfSegment)
//    {
//        i.first->setPointPosition(i.second, toPosition);
//    }
    m_firstKnotOfSegment->setPointPosition(ViewLine::Points::FirstPoint, toPosition);
     m_lastKnotOfSegment->setPointPosition(ViewLine::Points::LastPoint,  toPosition);

    printf("New position: %f, %f, %f\n", toPosition.x, toPosition.y, toPosition.z);
    std::cout << "" << std::endl;

    //    m_controller->mouseMove();
}

void ViewKnot::changeColor()
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

void ViewKnot::notifyLineAsFirstPoint(ViewSegment * segment)
{
    m_firstKnotOfSegment = segment;
}

void ViewKnot::notifyLineAsLastPoint(ViewSegment * segment)
{
    m_lastKnotOfSegment = segment;
}

ViewSegment *ViewKnot::segmentFirstKnotOf() const
{
    return m_firstKnotOfSegment;
}

ViewSegment *ViewKnot::segmentLastKnotOf() const
{
    return m_lastKnotOfSegment;
}

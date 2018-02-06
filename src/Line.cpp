#include "Line.hpp"

#include "geometryBuffer.hpp"

namespace glRender {

Line::Line(Vec3 p0, Vec3 p1, uint segmentsNumber, Vec3 color)
    : m_aabb(new AABB(Vec3(0,0,0), 1.0))
    , m_p0(p0)
    , m_p1(p1)
    , m_segmentsNumber(segmentsNumber)
    , m_color(color)
{
//    setSelectable(false);

    std::shared_ptr<Geometry> geometry = GeometryHelper::Line(p0, p1, segmentsNumber);

    Textures * textures = new Textures();

    std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::instance().shaderPrograms().get("coloredShP");

    shaderProgram->addAttribute<Vec3>("vertex");
    // shaderProgram->addAttribute<float>("index");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");

    shaderProgram->setUniform<Vec3>("color", m_color);

    shaderProgram->setUniform<Vec3>("color", m_color);

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(false);
    m_model->setDrawMode(Model::DrawMode::Lines);
    m_model->setOrigin(0.0, 0.0, 0.0);
}

Line::~Line()
{
    delete m_aabb;
}

void Line::update()
{
}

void Line::draw(Camera * camera)
{
    m_model->shaderProgram()->setUniform<Vec3>("color", m_color);
    m_model->setParentsMatrix(globalTransforms());

    m_model->draw(camera);
}

Model * Line::model()
{
    return m_model;
}

IBoundingBox * Line::bb() const
{
    return m_aabb;
}

}

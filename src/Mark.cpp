#include "Mark.hpp"

// #include "aabbNodeVisualizator.hpp"

namespace glRender {

Mark::Mark(Vec3 color, float size, uint i, uint j, uint k)
    : m_aabb(new AABB(Vec3(0,0,0), size))
    , m_color(color)
    , m_i(i)
    , m_j(j)
    , m_k(k)
{
    std::shared_ptr<Geometry> geometry = GeometryHelper::Box(size);

    Textures * textures = new Textures();

//    ShaderProgram * shaderProgram = ResourceManager::instance().getShaderProgram("data/colored.vertex", "data/colored.frag");
    // std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::instance().shaderPrograms().get("*", "data/colored.vertex", "data/colored.frag");
    std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::instance().shaderPrograms().get("coloredShP");
//    ShaderProgram * shaderProgram = new ShaderProgram("data/colored.vertex", "data/colored.frag");
    shaderProgram->addAttribute<Vec3>("vertex");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");
    shaderProgram->addUniform<Vec3>("color");

    shaderProgram->setUniform<Vec3>("color", m_color);

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(true);

    m_model->setOrigin(Vec3(-1500.0f + i * 2, 0, 0));
    m_aabb->setOrigin(m_model->origin());

    // m_aabbVisualizator = new AABBNodeVisualizator(m_aabb);
    // add(m_aabbVisualizator);
}

Mark::~Mark()
{
    delete m_aabb;
}

void Mark::update()
{
//    m_model->rotate(0.1, Vec3::AXE_Y());
    Vec3 pos = parentsTransforms() * m_model->origin();
    m_aabb->setOrigin(pos);
}

void Mark::draw(Camera * camera)
{
    m_model->shaderProgram()->setUniform<Vec3>("color", m_color);

    m_model->draw(camera/*, parentsTransforms()*/);
}

bool Mark::intersects(const RayPtr ray) const
{
    return m_aabb->intersects(ray);
}

Model * Mark::model() const
{
    return m_model;
}

IBoundingBox * Mark::bb() const
{
    return m_aabb;
}

void Mark::onMouseDown(Vec3 & position, RayPtr ray, Camera * camera)
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

void Mark::onMouseUp(Vec3 & position, RayPtr ray, Camera * camera)
{
    m_isSelected = false;
}

void Mark::onMouseMove(Vec3 & toPosition)
{
    model()->setOrigin(toPosition);
    bb()->setOrigin(toPosition);

    printf("New position: %f, %f, %f\n", toPosition.x, toPosition.y, toPosition.z);
    std::cout << "" << std::endl;

}

void Mark::changeColor()
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

}



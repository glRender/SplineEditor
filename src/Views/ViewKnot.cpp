#include "ViewKnot.hpp"

#include "ModelKnot.hpp"
#include "ViewSegment.hpp"
#include "ModelSplineEditor.hpp"

ViewKnot::ViewKnot(ModelKnot * model, ModelSplineEditor * modelSplineEditor)
    : m_model(model)
    , m_modelSplineEditor(modelSplineEditor)
    , m_aabb(new AABB(Vec3(0,0,0), 0.1))
    , m_currentColor(Vec3(0,1,0))
{
    std::shared_ptr<Geometry> geometry = GeometryHelper::Box(0.1);

    Textures * textures = new Textures();

    std::shared_ptr<ShaderProgram> shaderProgram = ResourceManager::instance().shaderPrograms().get("coloredShP");

    shaderProgram->addAttribute<Vec3>("vertex");

    shaderProgram->addUniform<Mat4>("projection");
    shaderProgram->addUniform<Mat4>("view");
    shaderProgram->addUniform<Mat4>("model");
    shaderProgram->addUniform<Vec3>("color");

    shaderProgram->setUniform<Vec3>("color", m_currentColor);

    m_mesh = new Model(geometry, textures, shaderProgram);
    m_mesh->setWireframeMode(true);

    const Vec3 position = {m_model->position().x(), m_model->position().y(), m_model->position().z()};
    setPosition(position);
}

ViewKnot::~ViewKnot()
{
    delete m_aabb;
}

void ViewKnot::draw(Camera *camera)
{
    m_mesh->shaderProgram()->setUniform<Vec3>("color", m_currentColor);
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

void ViewKnot::setPosition(const Vec3 & position)
{
    m_mesh->setOrigin(position);
    m_aabb->setOrigin(position);

    if (m_firstKnotOfSegment)
    {
        m_firstKnotOfSegment->setPointPosition(ViewLine::Points::FirstPoint, position);
    }

    if (m_lastKnotOfSegment)
    {
        m_lastKnotOfSegment->setPointPosition(ViewLine::Points::LastPoint,  position);
    }

    printf("New position: %f, %f, %f\n", position.x, position.y, position.z);
    std::cout << "" << std::endl;

}

void ViewKnot::setSelected(bool selected)
{
    if (selected == true)
    {
        m_currentColor = m_selectionColor;
    }
    else
    {
        m_currentColor = m_normalColor;
    }
    m_isSelected = selected;
}

bool ViewKnot::selected() const
{
    return m_isSelected;
}

void ViewKnot::setDragging(bool dragging)
{
    if (dragging == true)
    {
        m_currentColor = m_draggingColor;
    }
    else
    {
        if (m_isSelected == true)
        {
            m_currentColor = m_selectionColor;
        }
        else
        {
            m_currentColor = m_normalColor;
        }
    }
    m_isDragging = dragging;
}

bool ViewKnot::isDragging() const
{
    return m_isDragging;
}

void ViewKnot::onMouseUp(Vec3 &position, RayPtr ray, Camera * camera)
{
    if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Moving)
    {
        setDragging(false);
    }
    else if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Removing)
    {
        m_modelSplineEditor->modelSpline()->remove(m_model);
    }

}

void ViewKnot::onMouseDown(Vec3 &position, RayPtr ray, Camera * camera)
{
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

    std::cout << "Selected!" << std::endl;
    printf("The distance to plane of camera: %f\n", distance);
    std::cout << "" << std::endl;

    if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Selection)
    {
        setSelected( !selected() );
    }
    else if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Moving)
    {
        setDragging(true);
    }
}

void ViewKnot::onMouseMove(Vec3 &toPosition)
{
    if (m_modelSplineEditor->mode() == ModelSplineEditor::Mode::Moving)
    {
        m_model->setPosition({toPosition.x, toPosition.y, toPosition.z});
    }
}

void ViewKnot::changeColor(const Vec3 & color)
{
    m_currentColor = color;
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

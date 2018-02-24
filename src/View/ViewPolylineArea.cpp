#include "ViewPolylineArea.h"

#include <QDebug>

#include "SplineModel.hpp"
#include "KnotModel.hpp"

#include "CameraControl.hpp"

ViewPolylineArea::ViewPolylineArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void ViewPolylineArea::initializeGL()
{
    render = Render::instance();
    if (render == nullptr)
    {
        exit(3);
    }

    printf("%s\n", render->contextInformation());
    printf("%s\n", render->versionInformation());

    ///
    ResourceManager * resMng = &ResourceManager::instance();

    std::pair<const char *, std::map<ShaderType, const char *>> shadersPathes[] = {
        {"coloredShP",           {{ShaderType::VertexShader, "data/colored.vertex"},           {ShaderType::FragmentShader, "data/colored.frag"}}},
    };

    for (auto & i : shadersPathes)
    {
        resMng->shaderPrograms().create(i.first, [&i]() {
            return createShaderProgramFromFiles(i.second);
        });
    }
    ///

    camera = new PerspectiveCamera( 35.0, 16.0f/9.0f, 1.0f, 200.0f );
    camera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());

    scene = new Scene();
    scene->setCamera(camera);

    nodePicker = std::make_shared<NodePicker>(camera, scene);

    scene->add(new CameraControl(camera));

    m_spline = new SplineView();
    scene->add(m_spline);

    processModel();

    Render::instance()->scenes().add(scene);

    createAndStartDrawUpdater();
//    createAndStartLogicUpdater();

}

void ViewPolylineArea::resizeGL(int w, int h)
{
    render->setViewportSize(w, h);
}

void ViewPolylineArea::paintGL()
{
    render->drawFrame();
}

void ViewPolylineArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Vec2 normDeviceCoords(
            (float)event->pos().x() / width(),
            (float)event->pos().y() / height());

        nodePicker->mouseDownUnderNearest(normDeviceCoords);
    }
}

void ViewPolylineArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Vec2 normDeviceCoords(
            (float)event->pos().x() / width(),
            (float)event->pos().y() / height());

        nodePicker->mouseUpUnderNearest(normDeviceCoords);
    }
}

void ViewPolylineArea::mouseMoveEvent(QMouseEvent *event)
{
    Vec2 normDeviceCoords(
        (float)event->pos().x() / width(),
        (float)event->pos().y() / height());

    nodePicker->mouseMoveUnderNearest(normDeviceCoords);
}

void ViewPolylineArea::keyPressEvent(QKeyEvent *event)
{
    switch ( event->key() ) {
    case Qt::Key_W:
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::W);
        break;
    case Qt::Key_S:
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::S);
        break;
    case Qt::Key_A:
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::A);
        break;
    case Qt::Key_D:
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::D);
        break;
    case Qt::Key_Q:
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::Q);
        break;
    case Qt::Key_E:
        scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::E);
        break;

    default:
        event->ignore();
        break;
    }
}

void ViewPolylineArea::addMark(QSharedPointer<KnotModel> knot)
{
//    QVector3D position = knot->position();
//    Vec3 p = Vec3(position.x(), position.y(), position.z());
    SplineMarkView * m = new SplineMarkView(knot.data());
    m_spline->add(m);
    m_markByKnot[knot] = m;
}

void ViewPolylineArea::removeMark(QSharedPointer<KnotModel> knot)
{

}

void ViewPolylineArea::setModel(QSharedPointer<SplineModel> model)
{
    m_model = model;
}

void ViewPolylineArea::processModel()
{
    connect(m_model.data(), &SplineModel::added, this, [this](QSharedPointer<KnotModel> knot) {
        addMark(knot);
    });

    connect(m_model.data(), &SplineModel::removed, this, [this](QSharedPointer<KnotModel> knot) {
        removeMark(knot);
    });

    QList<QSharedPointer<KnotModel>> knots = m_model->knots().value;
    for (auto knot : knots)
    {
        addMark(knot);
    }
}

void ViewPolylineArea::createAndStartDrawUpdater()
{
    m_drawUpdater.setInterval(32);
    connect(&m_drawUpdater, &QTimer::timeout, this, [&]() {
//        scene->drawFrame();
        this->update();
    });
    m_drawUpdater.start();
}

void ViewPolylineArea::createAndStartLogicUpdater()
{
    m_logicUpdater.setInterval(64);
    connect(&m_logicUpdater, &QTimer::timeout, this, [&]() {
        scene->update();
        emit updated();
    });
    m_logicUpdater.start();
}

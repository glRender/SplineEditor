#include "ViewSplineArea.hpp"

#include <QDebug>

#include "ModelSpline.hpp"
#include "ModelKnot.hpp"

#include "CameraControl.hpp"

ViewSplineArea::ViewSplineArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void ViewSplineArea::initializeGL()
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

    m_spline = new ViewSpline();
    scene->add(m_spline);

    processModel();

    Render::instance()->scenes().add(scene);

    createAndStartDrawUpdater();
//    createAndStartLogicUpdater();

}

void ViewSplineArea::resizeGL(int w, int h)
{
    render->setViewportSize(w, h);
}

void ViewSplineArea::paintGL()
{
    render->drawFrame();
}

void ViewSplineArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Vec2 normDeviceCoords(
            (float)event->pos().x() / width(),
            (float)event->pos().y() / height());

        nodePicker->mouseDownUnderNearest(normDeviceCoords);
    }
}

void ViewSplineArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Vec2 normDeviceCoords(
            (float)event->pos().x() / width(),
            (float)event->pos().y() / height());

        nodePicker->mouseUpUnderNearest(normDeviceCoords);
    }
}

void ViewSplineArea::mouseMoveEvent(QMouseEvent *event)
{
    Vec2 normDeviceCoords(
        (float)event->pos().x() / width(),
        (float)event->pos().y() / height());

    nodePicker->mouseMoveUnderNearest(normDeviceCoords);
}

void ViewSplineArea::keyPressEvent(QKeyEvent *event)
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

void ViewSplineArea::addKnot(ControllerKnot * controllerKnot)
{
    ViewKnot * m = new ViewKnot(controllerKnot->model());
    m_spline->add(m);
    m_viewByModel[controllerKnot->model()] = m;
}

void ViewSplineArea::removeKnot(ControllerKnot * controllerKnot)
{

}

//void ViewSplineArea::setModel(QSharedPointer<ModelSpline> model)
//{
//    m_model = model;

//}

void ViewSplineArea::setController(ControllerSpline * controller)
{
    m_controller = controller;
}

void ViewSplineArea::processModel()
{
    if (m_controller)
    {
        connect(m_controller, &ControllerSpline::added, this, [this](ControllerKnot * knot) {
            addKnot(knot);
        });

        QList<ControllerKnot *> knots = m_controller->knotsControllers();
        for (auto knot : knots)
        {
            addKnot(knot);
        }
    }
    else
    {
        std::cout << "No controller! " << __FUNCTION__ << std::endl;
    }
}

void ViewSplineArea::createAndStartDrawUpdater()
{
    m_drawUpdater.setInterval(32);
    connect(&m_drawUpdater, &QTimer::timeout, this, [&]() {
//        scene->drawFrame();
        this->update();
    });
    m_drawUpdater.start();
}

void ViewSplineArea::createAndStartLogicUpdater()
{
    m_logicUpdater.setInterval(64);
    connect(&m_logicUpdater, &QTimer::timeout, this, [&]() {
        scene->update();
        emit updated();
    });
    m_logicUpdater.start();
}

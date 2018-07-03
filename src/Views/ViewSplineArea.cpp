#include "ViewSplineArea.hpp"

#include <QDebug>

#include "ModelSpline.hpp"
#include "ModelSplineEditor.hpp"
#include "ModelKnot.hpp"

#include "ViewSpline.hpp"

#include "CameraControl.hpp"

ViewSplineArea::ViewSplineArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void ViewSplineArea::setModel(ModelSplineEditor * modelEditor)
{
    m_modelSplineEditor = modelEditor;
    assert(m_modelSplineEditor);
}

void ViewSplineArea::processModel()
{
    assert(m_modelSplineEditor);
    assert(m_modelSplineEditor->modelSpline());

    m_viewSpline = new ViewSpline(m_modelSplineEditor->modelSpline(), m_modelSplineEditor);
    assert(m_viewSpline);
    m_scene->add(m_viewSpline);

    connect(m_modelSplineEditor->modelSpline(), &ModelSpline::added, this, [this](ModelKnot * knot) {
        assert(m_viewSpline);
        m_viewSpline->add(knot);
    });

    connect(m_modelSplineEditor->modelSpline(), &ModelSpline::removed, this, [this](ModelKnot * knot) {
        m_viewSpline->remove(knot);
    });

    connect(m_modelSplineEditor->modelSpline(), &ModelSpline::newSelection, this, [this](ModelKnot * knot) {
    });

    connect(m_modelSplineEditor->modelSpline(), &ModelSpline::loseSelection, this, [this](ModelKnot * knot) {
    });

}

void ViewSplineArea::initializeGL()
{
    render = Render::instance();
    if (render == nullptr)
    {
        exit(3);
    }

//    printf("%s\n", render->contextInformation());
//    printf("%s\n", render->versionInformation());

    ///
    ResourceManager * resMng = &ResourceManager::instance();

    shadersPathes = {
           {"coloredShP",           {{ShaderType::VertexShader, "data/colored.vertex"},           {ShaderType::FragmentShader, "data/colored.frag"}}},
       };

    for (auto i : shadersPathes)
    {
        resMng->shaderPrograms().create(i.first, [i]() {
            return createShaderProgramFromFiles(i.second);
        });
    }
    ///

    camera = new PerspectiveCamera( 35.0, 16.0f/9.0f, 1.0f, 200.0f );
    camera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());

    m_scene = new Scene();
    m_scene->setCamera(camera);

    nodePicker = std::make_shared<NodePicker>(camera, m_scene);

    m_scene->add(new CameraControl(camera));


    Render::instance()->scenes().add(m_scene);

    createAndStartDrawUpdater();
//    createAndStartLogicUpdater();

    processModel();

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
    GLContextKeeper keeper(this);

    if (event->button() == Qt::LeftButton)
    {
        Vec2 normDeviceCoords(
            (float)event->pos().x() / width(),
            (float)event->pos().y() / height());

        ModelSplineEditor::Mode mode = m_modelSplineEditor->mode();
        if (mode == ModelSplineEditor::Mode::Addition)
        {
            Vec3 p = nodePicker->coordOnDistance(normDeviceCoords, 1);
            m_modelSplineEditor->modelSpline()->add({p.x, p.y, p.z});
        }
        else if (mode == ModelSplineEditor::Mode::Removing || mode == ModelSplineEditor::Mode::Selection || mode == ModelSplineEditor::Mode::Moving)
        {
            nodePicker->mouseDownUnderNearest(normDeviceCoords);
        }

    }
    else if (event->button() == Qt::RightButton)
    {
    }
}

void ViewSplineArea::mouseReleaseEvent(QMouseEvent *event)
{
    GLContextKeeper keeper(this);

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
    GLContextKeeper keeper(this);

    Vec2 normDeviceCoords(
        (float)event->pos().x() / width(),
        (float)event->pos().y() / height());

    nodePicker->mouseMoveUnderNearest(normDeviceCoords);
}

void ViewSplineArea::keyPressEvent(QKeyEvent *event)
{
    GLContextKeeper keeper(this);

    switch ( event->key() ) {
    case Qt::Key_W:
        m_scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::W);
        break;
    case Qt::Key_S:
        m_scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::S);
        break;
    case Qt::Key_A:
        m_scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::A);
        break;
    case Qt::Key_D:
        m_scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::D);
        break;
    case Qt::Key_Q:
        m_scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::Q);
        break;
    case Qt::Key_E:
        m_scene->processKeyboardsKeys(IKeyPressable::KeyboardKey::E);
        break;

    default:
        event->ignore();
        break;
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
        m_scene->update();
        emit updated();
    });
    m_logicUpdater.start();
}

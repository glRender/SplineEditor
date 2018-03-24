#include "ViewSplineArea.hpp"

#include <QDebug>

#include "ModelSpline.hpp"
#include "ModelSplineEditor.hpp"
#include "ModelKnot.hpp"

#include "CameraControl.hpp"

ViewSplineArea::ViewSplineArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void ViewSplineArea::setModel(ModelSplineEditor * modelEditor)
{
    m_modelSplineEditor = modelEditor;
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

void ViewSplineArea::processModel()
{
    auto addViewKnot = [this](ModelKnot * modelKnot) {
        ViewKnot * viewKnot = new ViewKnot(modelKnot, m_modelSplineEditor);

        connect(modelKnot, &ModelKnot::changed, this, [viewKnot, modelKnot]() {
            viewKnot->setPosition({modelKnot->position().x(), modelKnot->position().y(), modelKnot->position().z()});
        });

        m_viewSpline->add(viewKnot);
    };

    auto removeViewKnot = [this](ModelKnot * modelKnot) {
        printf("Let spline view remove knot!\n");

        ViewKnot * viewKnot = m_viewSpline->byModelKnot(modelKnot);
        if (viewKnot)
        {            
            m_viewSpline->remove(viewKnot);
        }

    };

    if (m_modelSplineEditor != nullptr)
    {
        m_viewSpline = new ViewSpline(m_modelSplineEditor->modelSpline());
        scene->add(m_viewSpline);

        connect(m_modelSplineEditor->modelSpline(), &ModelSpline::added, this, [this, addViewKnot](ModelKnot * knot) {
            addViewKnot(knot);
        });

        connect(m_modelSplineEditor->modelSpline(), &ModelSpline::removed, this, [this, removeViewKnot](ModelKnot * knot) {
            removeViewKnot(knot);
        });

        auto knots = m_modelSplineEditor->modelSpline()->knotModels();
        for (auto knot : knots)
        {
            addViewKnot(knot);
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

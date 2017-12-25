#include "polylinearea.h"

#include <QDebug>

#include "Mark.hpp"

void PolylineArea::createAndStartDrawUpdater()
{
    m_drawUpdater.setInterval(32);
    connect(&m_drawUpdater, &QTimer::timeout, this, [&]() {
//        scene->drawFrame();
        this->update();
    });
    m_drawUpdater.start();
}

void PolylineArea::createAndStartLogicUpdater()
{
    m_logicUpdater.setInterval(64);
    connect(&m_logicUpdater, &QTimer::timeout, this, [&]() {
        scene->update();
        emit updated();
    });
    m_logicUpdater.start();
}

PolylineArea::PolylineArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void PolylineArea::initializeGL()
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

    scene->add(new CameraNode(camera));

    srand( time(0) );

    for (int i=0; i<3000; i++)
    {
        Mark * n = new Mark(Vec3(0,1,0),1,i,0,0);
        scene->add(n);
    }

    Render::instance()->scenes().add(scene);

    createAndStartDrawUpdater();
//    createAndStartLogicUpdater();

}

void PolylineArea::resizeGL(int w, int h)
{
    render->setViewportSize(w, h);
}

void PolylineArea::paintGL()
{
    render->drawFrame();
}

void PolylineArea::mouseReleaseEvent(QMouseEvent *event)
{

}

void PolylineArea::keyPressEvent(QKeyEvent *event)
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

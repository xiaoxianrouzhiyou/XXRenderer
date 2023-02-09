#include "BBOpenGLWidget.h"
#include <QMatrix4x4>
#include "Utils/BBUtils.h"
#include "Scene/BBScene.h"

BBOpenGLWidget::BBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_pScene = new BBScene();
}

BBOpenGLWidget::~BBOpenGLWidget()
{
    BB_SAFE_DELETE(m_pScene);
}

void BBOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    QMatrix4x4 mat;
    mat.perspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    glLoadMatrixf(mat.data());

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_pScene->init();
}

void BBOpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width * devicePixelRatio(), height * devicePixelRatio());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    QMatrix4x4 mat;
    mat.perspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    glLoadMatrixf(mat.data());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_pScene->resize(width, height);
}

void BBOpenGLWidget::paintGL()
{
    glClearColor(0.141f, 0.169f, 0.227f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE);

    m_pScene->render();
}

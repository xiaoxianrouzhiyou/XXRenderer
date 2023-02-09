#include "BBScene.h"
#include "Renderer/BBCamera.h"
#include "3D/BBModel.h"
#include "Renderer/BBRenderState.h"

BBScene::BBScene()
{
    m_fUpdateRate = (float) BB_CONSTANT_UPDATE_RATE / 1000;

    m_pCamera = nullptr;
    m_pSphere = nullptr;
}

BBScene::~BBScene()
{
    BB_SAFE_DELETE(m_pCamera);
    BB_SAFE_DELETE(m_pSphere);
}

void BBScene::init()
{
    BBGlobalRenderState::init();

    m_pCamera = new BBCamera();

    m_pSphere = new BBModel(BBMeshType::OBJ);
    m_pSphere->init(BB_PATH_RESOURCE_MESH(sphere.obj));
}

void BBScene::resize(float width, float height)
{
    // 3D camera, resize
    m_pCamera->setViewportSize(width, height);
}

void BBScene::render()
{
    // 3D camera mode
    m_pCamera->switchTo3D();
    // refresh camera position and direction, update pos and ..., Convenient for subsequent use
    m_pCamera->update(m_fUpdateRate);

    m_pSphere->render(m_pCamera);

    // 2D camera mode
    m_pCamera->switchTo2D();
}

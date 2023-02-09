#include "BBRenderableObject.h"
#include "Renderer/BBDrawCall.h"
#include "Renderer/BBElementBufferObject.h"
#include "Renderer/BBVertexBufferObject.h"

BBRenderableObject::BBRenderableObject()
    : BBRenderableObject(0, 0, 0, 0, 0, 0, 1, 1, 1)
{

}

BBRenderableObject::BBRenderableObject(const QVector3D &position, const QVector3D &rotation, const QVector3D &scale)
    : BBRenderableObject(position.x(), position.y(), position.z(),
                         rotation.x(), rotation.y(), rotation.z(),
                            scale.x(),    scale.y(),    scale.z())
{

}

BBRenderableObject::BBRenderableObject(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz)
    : BBObject(px, py, pz, rx, ry, rz, sx, sy, sz)
{
    sharedInit();
}

BBRenderableObject::~BBRenderableObject()
{
    BB_SAFE_DELETE(m_pVBO);
    BB_SAFE_DELETE(m_pEBO);
    BB_SAFE_DELETE_ARRAY(m_pIndexes);
}

void BBRenderableObject::init()
{
    m_pCurrentMaterial->setMatrix4(LOCATION_MODELMATRIX, m_ModelMatrix.data());

    if (m_nIndexCount > 0)
    {
        m_pEBO = new BBElementBufferObject(m_nIndexCount);
        m_pEBO->submitData(m_pIndexes, m_nIndexCount);
    }

    if (m_pVBO)
    {
        m_pVBO->submitData();
        m_nVertexCount = m_pVBO->getVertexCount();
    }
}

void BBRenderableObject::render(BBCamera *pCamera)
{
    render(m_ModelMatrix, pCamera);
}

void BBRenderableObject::render(const QMatrix4x4 &modelMatrix, BBCamera *pCamera)
{
    m_pDrawCalls->draw(pCamera);
}

void BBRenderableObject::appendDrawCall(BBDrawCall *pDrawCall)
{
    if (m_pDrawCalls == nullptr)
    {
        m_pDrawCalls = pDrawCall;
    }
    else
    {
        m_pDrawCalls->pushBack(pDrawCall);
    }
}

void BBRenderableObject::sharedInit()
{
    m_pDrawCalls = nullptr;
    m_pCurrentMaterial = new BBMaterial();
    m_pVBO = nullptr;
    m_pEBO = nullptr;
    m_pIndexes = nullptr;
    m_nIndexCount = 0;
    m_nVertexCount = 0;
    m_DefaultColor = QVector3D(1.0f, 1.0f, 1.0f);
}

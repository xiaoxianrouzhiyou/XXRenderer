#include "BBDrawCall.h"
#include "Renderer/BBRenderPass.h"
#include "Renderer/BBElementBufferObject.h"
#include "Renderer/BBVertexBufferObject.h"

BBDrawCall::BBDrawCall()
    : BBBaseRenderComponent()
{
    m_pMaterial = nullptr;

    m_eDrawPrimitiveType = GL_TRIANGLES;
    m_nDrawStartIndex = 0;

    m_pVBO = nullptr;
    m_nDrawCount = 3;
    m_pEBO = nullptr;
    m_nIndexCount = 0;

    m_bVisible = true;
}

void BBDrawCall::setMaterial(BBMaterial *pMaterial)
{
    m_pMaterial = pMaterial;
    m_pMaterial->bindDrawCallInstance(this);
}

void BBDrawCall::setVBO(BBVertexBufferObject *pVBO, GLenum eDrawPrimitiveType, int nDrawStartIndex, int nDrawCount)
{
    m_pVBO = pVBO;
    m_eDrawPrimitiveType = eDrawPrimitiveType;
    m_nDrawStartIndex = nDrawStartIndex;
    m_nDrawCount = nDrawCount;
}

void BBDrawCall::setEBO(BBElementBufferObject *pEBO, GLenum eDrawPrimitiveType, int nIndexCount, int nDrawStartIndex)
{
    m_pEBO = pEBO;
    m_eDrawPrimitiveType = eDrawPrimitiveType;
    m_nIndexCount = nIndexCount;
    m_nDrawStartIndex = nDrawStartIndex;
}

void BBDrawCall::draw(BBCamera *pCamera)
{
    renderForwardPass(pCamera);
}

void BBDrawCall::renderForwardPass(BBCamera *pCamera)
{
    if (m_bVisible)
    {
        bindVBO();

        // base
//        if (lights.count() > 0)
//        {
//            // render the first light
//            BBLight *pLight = (BBLight*)lights[0];
//            pLight->setRenderPass(m_pMaterial->getBaseRenderPass());
//        }
        m_pMaterial->getBaseRenderPass()->bind(pCamera);
        if (m_pEBO == nullptr)
        {
            drawVBO(m_eDrawPrimitiveType, m_nDrawStartIndex, m_nDrawCount);
        }
        else
        {
            m_pEBO->bind();
            m_pEBO->draw(m_eDrawPrimitiveType, m_nIndexCount, m_nDrawStartIndex);
            m_pEBO->unbind();
        }
        m_pMaterial->getBaseRenderPass()->unbind();

        // additive
        // to do

        unbindVBO();
    }

    if (m_pNext != nullptr)
    {
        next<BBDrawCall>()->draw(pCamera);
    }
}

void BBDrawCall::bindVBO()
{
    m_pVBO->bind();
}

void BBDrawCall::unbindVBO()
{
    m_pVBO->unbind();
}

void BBDrawCall::drawVBO(GLenum eDrawPrimitiveType, int nDrawStartIndex, int nDrawCount)
{
    m_pVBO->draw(eDrawPrimitiveType, nDrawStartIndex, nDrawCount);
}

#include "BBMaterial.h"
#include "BBRenderPass.h"
#include "Shader/BBShader.h"
#include "BBDrawCall.h"

BBMaterial::BBMaterial()
{

}

BBMaterial::~BBMaterial()
{
    BB_SAFE_DELETE(m_pBaseRenderPass);
    BB_SAFE_DELETE(m_pAdditiveRenderPass);
}

void BBMaterial::init(const char *shaderName, const QString &vShaderPath, const QString &fShaderPath, const QString &gShaderPath)
{
    m_pBaseRenderPass = new BBRenderPass();
    m_pBaseRenderPass->setShader(BBShader::loadShader(shaderName, vShaderPath, fShaderPath, gShaderPath));
}

void BBMaterial::initMultiPass(const char *shaderName, const QString &vShaderPath, const QString &fShaderPath, const QString &gShaderPath)
{
    init(shaderName, vShaderPath, fShaderPath, gShaderPath);
    m_pAdditiveRenderPass = new BBRenderPass();
    m_pAdditiveRenderPass->setShader(BBShader::loadShader(shaderName, vShaderPath, fShaderPath, gShaderPath));
}

void BBMaterial::setBlendState(bool bEnable)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setBlendState(bEnable);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setBlendState(bEnable);
    }
}

void BBMaterial::setSRCBlendFunc(unsigned int src)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setSRCBlendFunc(src);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setSRCBlendFunc(src);
    }
}

void BBMaterial::setDSTBlendFunc(unsigned int dst)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setDSTBlendFunc(dst);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setDSTBlendFunc(dst);
    }
}

void BBMaterial::setBlendFunc(unsigned int src, unsigned int dst)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setBlendFunc(src, dst);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setBlendFunc(src, dst);
    }
}

void BBMaterial::setZTestState(bool bEnable)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setZTestState(bEnable);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setZTestState(bEnable);
    }
}

void BBMaterial::setZFunc(unsigned int func)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setZFunc(func);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setZFunc(func);
    }
}

void BBMaterial::setZMask(bool bEnable)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setZMask(bEnable);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setZMask(bEnable);
    }
}

void BBMaterial::setStencilMask(bool bEnable)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setStencilMask(bEnable);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setStencilMask(bEnable);
    }
}

void BBMaterial::setCullState(bool bEnable)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setCullState(bEnable);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setCullState(bEnable);
    }
}

void BBMaterial::setCullFace(int face)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setCullFace(face);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setCullFace(face);
    }
}

bool BBMaterial::getBlendState()
{
    return m_pBaseRenderPass->getBlendState();
}

unsigned int BBMaterial::getSRCBlendFunc()
{
    return m_pBaseRenderPass->getSRCBlendFunc();
}

unsigned int BBMaterial::getDSTBlendFunc()
{
    return m_pBaseRenderPass->getDSTBlendFunc();
}

bool BBMaterial::getCullState()
{
    return m_pBaseRenderPass->getCullState();
}

int BBMaterial::getCullFace()
{
    return m_pBaseRenderPass->getCullFace();
}

void BBMaterial::setFloat(const std::string &uniformName, const float fValue)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setFloat(uniformName, fValue);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setFloat(uniformName, fValue);
    }
}

void BBMaterial::setMatrix4(const std::string &uniformName, const float *pMatrix4)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setMatrix4(uniformName, pMatrix4);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setMatrix4(uniformName, pMatrix4);
    }
}

void BBMaterial::setVector4(const std::string &uniformName, float x, float y, float z, float w)
{
    float *value = new float[4] {x, y, z, w};
    setVector4(uniformName, value);
}

void BBMaterial::setVector4(const std::string &uniformName, const float *pVector4)
{
    if (m_pBaseRenderPass != nullptr)
    {
        m_pBaseRenderPass->setVector4(uniformName, pVector4);
    }
    if (m_pAdditiveRenderPass != nullptr)
    {
        m_pAdditiveRenderPass->setVector4(uniformName, pVector4);
    }
}

#ifndef BBMATERIAL_H
#define BBMATERIAL_H


#include "BBBaseRenderComponent.h"

class BBCamera;
class BBAttribute;
class BBUniformUpdater;
class BBMaterialProperty;
class BBRenderPass;
class BBShader;
class BBDrawCall;
class BBMaterial
{
public:
    BBMaterial();
    ~BBMaterial();

    void init(const char *shaderName, const QString &vShaderPath, const QString &fShaderPath, const QString &gShaderPath = "");
    void initMultiPass(const char *shaderName, const QString &vShaderPath, const QString &fShaderPath, const QString &gShaderPath = "");

    void bindDrawCallInstance(BBDrawCall *pDrawCall) { m_pDrawCallInstance = pDrawCall; }

public:
    void setBlendState(bool bEnable);
    void setSRCBlendFunc(unsigned int src);
    void setDSTBlendFunc(unsigned int dst);
    void setBlendFunc(unsigned int src, unsigned int dst);
    void setZTestState(bool bEnable);
    void setZFunc(unsigned int func);
    void setZMask(bool bEnable);
    void setStencilMask(bool bEnable);
    void setCullState(bool bEnable);
    void setCullFace(int face);

    bool getBlendState();
    unsigned int getSRCBlendFunc();
    unsigned int getDSTBlendFunc();
    bool getCullState();
    int getCullFace();

public:
    void setFloat(const std::string &uniformName, const float fValue);
    void setMatrix4(const std::string &uniformName, const float *pMatrix4);
    void setVector4(const std::string &uniformName, float x, float y, float z, float w);
    void setVector4(const std::string &uniformName, const float *pVector4);

public:
    void setBaseRenderPass(BBRenderPass *pRenderPass) { m_pBaseRenderPass = pRenderPass; }
    inline BBRenderPass* getBaseRenderPass() const { return m_pBaseRenderPass; }
    void setAdditiveRenderPass(BBRenderPass *pRenderPass) { m_pAdditiveRenderPass = pRenderPass; }
    inline BBRenderPass* getAdditiveRenderPass() const { return m_pAdditiveRenderPass; }

private:
    BBRenderPass *m_pBaseRenderPass;
    BBRenderPass *m_pAdditiveRenderPass;
    BBDrawCall *m_pDrawCallInstance;
};

#endif // BBMATERIAL_H

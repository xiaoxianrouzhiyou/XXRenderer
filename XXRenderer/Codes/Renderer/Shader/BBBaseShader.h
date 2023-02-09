#ifndef BBBASESHADER_H
#define BBBASESHADER_H


#include "Renderer/BBBaseRenderComponent.h"
#include "Renderer/BBMaterialProperty.h"

class BBAttribute;
class BBUniformUpdater;
class BBBaseShader : public BBBaseRenderComponent
{
public:
    BBBaseShader();

    inline GLuint getProgram() const { return m_Program; }
    void activeAttributes();
    inline BBUniformUpdater* getUniforms() { return m_pUniforms; }
    inline bool isWriteFBO() { return m_bWriteFBO; }

protected:
    void initAttributes();
    void initUniforms();
    BBUniformUpdater* initUniformFloat(GLint location, const char *pUniformName);
    BBUniformUpdater* initUniformFloatArray(GLint location, const char *pUniformName, int nArrayCount);
    BBUniformUpdater* initUniformMatrix4(GLint location, const char *pUniformName);
    BBUniformUpdater* initUniformVector4(GLint location, const char *pUniformName);
    BBUniformUpdater* initUniformVector4Array(GLint location, const char *pUniformName, int nArrayCount);
    BBUniformUpdater* initUniformSampler2D(GLint location, const char *pUniformName, int &nSlotIndex);
    BBUniformUpdater* initUniformSampler3D(GLint location, const char *pUniformName, int &nSlotIndex);
    BBUniformUpdater* initUniformSamplerCube(GLint location, const char *pUniformName, int &nSlotIndex);
    void appendUniformUpdater(BBUniformUpdater *pUniformUpdater);

    GLuint compileShader(GLenum shaderType, const char *shaderCode);

    GLuint m_Program;
    BBAttribute *m_pAttributes;
    BBUniformUpdater *m_pUniforms;
    QMap<std::string, BBMaterialProperty*> m_Properties;

    bool m_bWriteFBO;
};

#endif // BBBASESHADER_H

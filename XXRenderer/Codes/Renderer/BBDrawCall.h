#ifndef BBDRAWCALL_H
#define BBDRAWCALL_H


#include "BBMaterial.h"
#include "Utils/BBLinkedList.h"

class BBCamera;
class BBVertexBufferObject;
class BBElementBufferObject;
class BBObject;
class BBDrawCall : public BBBaseRenderComponent, public BBLinkedList
{
public:
    BBDrawCall();

    void setMaterial(BBMaterial *pMaterial);
    void setVBO(BBVertexBufferObject *pVBO, GLenum eDrawPrimitiveType = GL_TRIANGLES, int nDrawStartIndex = 0, int nDrawCount = 3);
    void setEBO(BBElementBufferObject *pEBO, GLenum eDrawPrimitiveType, int nIndexCount, int nDrawStartIndex);

public:
    void draw(BBCamera *pCamera);
    void renderForwardPass(BBCamera *pCamera);

public:
    inline BBMaterial* getMaterial() { return m_pMaterial; }

public:
    void bindVBO();
    void unbindVBO();
    void drawVBO(GLenum eDrawPrimitiveType, int nDrawStartIndex, int nDrawCount);

private:
    BBMaterial *m_pMaterial;

    GLenum m_eDrawPrimitiveType;
    int m_nDrawStartIndex;

    BBVertexBufferObject *m_pVBO;

    int m_nDrawCount;
    BBElementBufferObject *m_pEBO;
    int m_nIndexCount;

    bool m_bVisible;
};

#endif // BBDRAWCALL_H

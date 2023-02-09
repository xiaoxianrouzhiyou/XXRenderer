#ifndef BBSCENE_H
#define BBSCENE_H


#include "Renderer/BBBaseRenderComponent.h"

class BBCamera;
class BBModel;
class BBScene
{
public:
    BBScene();
    ~BBScene();

    void init();
    void resize(float width, float height);
    void render();

private:
    float m_fUpdateRate;

    BBCamera *m_pCamera;
    BBModel *m_pSphere;
};

#endif // BBSCENE_H

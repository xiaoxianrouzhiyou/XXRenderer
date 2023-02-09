#ifndef BBMODEL_H
#define BBMODEL_H


#include "Base/BBObject.h"
#include "BBMesh.h"

class BBMesh;
class BBModel : public BBObject
{
public:
    BBModel(const BBMeshType &eType);
    BBModel(const QVector3D &position, const QVector3D &rotation, const QVector3D &scale, const BBMeshType &eType);
    BBModel(float px, float py, float pz,
            float rx, float ry, float rz,
            float sx, float sy, float sz, const BBMeshType &eType);
    ~BBModel() override;

    void init(const QString &userData) override;
    void render(BBCamera *pCamera) override;

protected:
    BBMesh *m_pMesh;
//    BBBoundingBox3D *m_pBoundingBox;
};

#endif // BBMODEL_H

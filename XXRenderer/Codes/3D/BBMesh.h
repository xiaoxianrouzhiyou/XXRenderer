#ifndef BBMESH_H
#define BBMESH_H


#include "Base/BBRenderableObject.h"


enum BBMeshType
{
    OBJ = 0x01,
    FBX = 0x02,
    TERRAIN = 0x04,
    AREALIGHT = 0x08,
    PROCEDURE_MESH = 0x16
};

class BBBoundingBox3D;
class BBRay;
class BBMesh : public BBRenderableObject
{
public:
    BBMesh();
    BBMesh(float px, float py, float pz,
           float rx, float ry, float rz,
           float sx, float sy, float sz);
    ~BBMesh() override;

    void initByMeshFilePath(const QString &path);

protected:
    void load(const QString &path, QList<QVector4D> &outPositions);

    GLenum m_eDrawPrimitiveType;
};
#endif // BBMESH_H

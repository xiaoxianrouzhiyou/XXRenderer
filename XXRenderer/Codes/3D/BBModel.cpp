#include "BBModel.h"
#include "Utils/BBUtils.h"

BBModel::BBModel(const BBMeshType &eType)
    : BBModel(0, 0, 0, 0, 0, 0, 1, 1, 1, eType)
{

}

BBModel::BBModel(const QVector3D &position, const QVector3D &rotation, const QVector3D &scale, const BBMeshType &eType)
    : BBModel(position.x(), position.y(), position.z(),
              rotation.x(), rotation.y(), rotation.z(),
                 scale.x(),    scale.y(),    scale.z(), eType)
{

}

BBModel::BBModel(float px, float py, float pz,
                 float rx, float ry, float rz,
                 float sx, float sy, float sz, const BBMeshType &eType)
    : BBObject(px, py, pz, rx, ry, rz, sx, sy, sz)
{
    if (eType == BBMeshType::OBJ)
    {
        m_pMesh = new BBMesh(px, py, pz, rx, ry, rz, sx, sy, sz);
    }
//    m_pBoundingBox = nullptr;
}

BBModel::~BBModel()
{
    BB_SAFE_DELETE(m_pMesh);
//    BB_SAFE_DELETE(m_pBoundingBox);
}

void BBModel::init(const QString &userData)
{
    BBObject::init(userData);
    m_pMesh->initByMeshFilePath(userData);
}

void BBModel::render(BBCamera *pCamera)
{
    m_pMesh->render(pCamera);
//    m_pBoundingBox->render(pCamera);
}

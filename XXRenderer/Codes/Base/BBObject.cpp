#include "BBObject.h"

BBObject::BBObject()
    : BBObject(0, 0, 0, 0, 0, 0, 1, 1, 1)
{

}

BBObject::BBObject(const QVector3D &position, const QVector3D &rotation, const QVector3D &scale)
    : BBObject(position.x(), position.y(), position.z(),
               rotation.x(), rotation.y(), rotation.z(),
                  scale.x(),    scale.y(),    scale.z())
{

}

BBObject::BBObject(float px, float py, float pz,
                   float rx, float ry, float rz,
                   float sx, float sy, float sz)
{
    m_Position        = QVector3D(px, py, pz);
    m_Rotation        = QVector3D(rx, ry, rz);
    m_Scale           = QVector3D(sx, sy, sz);
    m_Quaternion      = QQuaternion::fromEulerAngles(m_Rotation);
    setModelMatrix(px, py, pz, m_Quaternion, sx, sy, sz);
}

BBObject::~BBObject()
{

}

void BBObject::init()
{

}

void BBObject::init(const QString &path)
{
    m_strFilePath = path;
}

void BBObject::render()
{

}

void BBObject::render(BBCamera *pCamera)
{
    Q_UNUSED(pCamera);
}

void BBObject::render(BBCanvas *pCanvas)
{
    Q_UNUSED(pCanvas);
}

void BBObject::render(const QMatrix4x4 &modelMatrix, BBCamera *pCamera)
{
    Q_UNUSED(modelMatrix);
    Q_UNUSED(pCamera);
}

void BBObject::resize(float fWidth, float fHeight)
{
    Q_UNUSED(fWidth);
    Q_UNUSED(fHeight);
}

void BBObject::setModelMatrix(float px, float py, float pz,
                              const QQuaternion &r,
                              float sx, float sy, float sz)
{
    m_ModelMatrix.setToIdentity();
    m_ModelMatrix.translate(px, py, pz);
    m_ModelMatrix.rotate(r);
    m_ModelMatrix.scale(sx, sy, sz);
}


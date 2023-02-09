#ifndef BBOBJECT_H
#define BBOBJECT_H


#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>

class BBCamera;
class BBCanvas;
class BBObject
{
public:
    BBObject();
    BBObject(const QVector3D &position, const QVector3D &rotation, const QVector3D &scale);
    BBObject(float px, float py, float pz,
             float rx, float ry, float rz,
             float sx, float sy, float sz);
    virtual ~BBObject();

    virtual void init();
    virtual void init(const QString &path);
    virtual void render();
    virtual void render(BBCamera *pCamera);
    virtual void render(BBCanvas *pCanvas);
    virtual void render(const QMatrix4x4 &modelMatrix, BBCamera *pCamera);
    virtual void resize(float fWidth, float fHeight);

protected:
    virtual void setModelMatrix(float px, float py, float pz,
                                const QQuaternion &r,
                                float sx, float sy, float sz);
    QVector3D m_Position;
    QVector3D m_Rotation;
    QQuaternion m_Quaternion;
    QVector3D m_Scale;
    QMatrix4x4 m_ModelMatrix;

    QString m_strFilePath;
};

#endif // XXOBJECT_H

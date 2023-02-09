#ifndef BBRAY_H
#define BBRAY_H


#include "Renderer/BBBaseRenderComponent.h"
#include <cfloat>

class BBModel;

enum BBPlaneName
{
    XOY = 0,
    XOZ = 1,
    YOZ = 2
};

struct BBHitInfo
{
    BBHitInfo()
    {
        m_fDistance = FLT_MAX;
        m_pModel = nullptr;
    }

    QVector3D m_Position;
    QVector2D m_Texcoords;
    QVector3D m_Normal;
    float m_fDistance;
    BBModel *m_pModel;
};

class BBRay
{
public:
    BBRay(const QVector3D &origin = QVector3D(0, 0, 0), const QVector3D &direction = QVector3D(0, 0, -1));
    BBRay(const GLdouble &nearX, const GLdouble &nearY, const GLdouble &nearZ,
          const GLdouble &farX, const GLdouble &farY, const GLdouble &farZ);

    void setRay(const QVector3D &origin = QVector3D(0, 0, 0), const QVector3D &direction = QVector3D(0, 0, -1));

    QVector3D computeIntersectWithXOZPlane(float y) const;
    QVector3D computeIntersectWithXOYPlane(float z) const;
    QVector3D computeIntersectWithYOZPlane(float x) const;

    bool computeIntersectWithPlane(const QVector3D &point1, const QVector3D &point2, const QVector3D &point3, QVector3D &outIntersection) const;
    bool computeIntersectWithPlane(const QVector3D &point1, const QVector3D &point2, const QVector3D &point3, QVector3D &outNormal, QVector3D &outIntersection) const;
    bool computeIntersectWithPlane(const QVector3D &point, const QVector3D &normal, QVector3D &outIntersection) const;
    bool computeIntersectWithTriangle(const QVector3D &point1, const QVector3D &point2, const QVector3D &point3, QVector3D &outIntersection) const;
    bool computeIntersectWithTriangle(const QVector3D &point1, const QVector3D &point2, const QVector3D &point3,
                                      QVector3D &outNormal, QVector3D &outIntersectionPos, float &outIntersectionU, float &outIntersectionV) const;
    bool computeIntersectWithRectangle(const QVector3D &point1, const QVector3D &point2, const QVector3D &point3, const QVector3D &point4, QVector3D &outIntersection) const;

    float computeIntersectDistance(const QVector3D &intersection) const;

    // Circle parallel to coordinate plane
    bool computeIntersectWithCircle(const QVector3D &center, float fRadius, const BBPlaneName &ePlaneName, QVector3D &outIntersection) const;
    bool computeIntersectWithQuarterCircle(const QVector3D &center, float fRadius, const BBPlaneName &ePlaneName, QVector3D &outIntersection, const QVector3D &quadrantFlag) const;

    QVector3D getDirection() const { return m_Direction; }

    inline QVector3D getNearPoint() { return m_NearPoint; }
    inline QVector3D getFarPoint() { return m_FarPoint; }

private:
    QVector3D m_NearPoint;
    QVector3D m_FarPoint;
    QVector3D m_Direction;
};

#endif // BBRAY_H

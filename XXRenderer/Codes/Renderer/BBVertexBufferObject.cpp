#include "BBVertexBufferObject.h"

BBVertexBufferObject::BBVertexBufferObject()
    : BBBufferObject()
{
    m_pVertexes = nullptr;
    // without setSize
}

BBVertexBufferObject::BBVertexBufferObject(int nVertexCount)
    : BBBufferObject()
{
    m_pVertexes = nullptr;
    setSize(nVertexCount);
}

BBVertexBufferObject::~BBVertexBufferObject()
{
    BB_SAFE_DELETE_ARRAY(m_pVertexes);
}

void BBVertexBufferObject::setPosition(int index, float x, float y, float z, float w)
{
    m_pVertexes[index].m_fPosition[0] = x;
    m_pVertexes[index].m_fPosition[1] = y;
    m_pVertexes[index].m_fPosition[2] = z;
    m_pVertexes[index].m_fPosition[3] = w;
}

void BBVertexBufferObject::setPosition(int index, const QVector3D &position)
{
    setPosition(index, position.x(), position.y(), position.z());
}

void BBVertexBufferObject::setPosition(int index, const QVector4D &position)
{
    setPosition(index, position.x(), position.y(), position.z(), position.w());
}

QVector3D BBVertexBufferObject::getPosition(int index)
{
    return QVector3D(m_pVertexes[index].m_fPosition[0], m_pVertexes[index].m_fPosition[1], m_pVertexes[index].m_fPosition[2]);
}

QList<QVector4D> BBVertexBufferObject::getPositions()
{
    QList<QVector4D> vertexes;
    for (int i = 0; i < m_nVertexCount; i++)
    {
        vertexes.append(QVector4D(getPosition(i), 1.0f));
    }
    return vertexes;
}

QList<QVector3D> BBVertexBufferObject::getNonHomogeneousPositions()
{
    QList<QVector3D> vertexes;
    for (int i = 0; i < m_nVertexCount; i++)
    {
        vertexes.append(getPosition(i));
    }
    return vertexes;
}

void BBVertexBufferObject::setColor(float r, float g, float b, float a)
{
    for (int i = 0; i < m_nVertexCount; i++)
    {
        setColor(i, r, g, b, a);
    }
    submitData();
}

void BBVertexBufferObject::setColor(int index, float r, float g, float b, float a)
{
    m_pVertexes[index].m_fColor[0] = r;
    m_pVertexes[index].m_fColor[1] = g;
    m_pVertexes[index].m_fColor[2] = b;
    m_pVertexes[index].m_fColor[3] = a;
}

void BBVertexBufferObject::setColor(int index, const QVector3D &rgb)
{
    setColor(index, rgb.x(), rgb.y(), rgb.z());
}

void BBVertexBufferObject::setColor(int index, const QVector4D &rgba)
{
    setColor(index, rgba.x(), rgba.y(), rgba.z(), rgba.w());
}

QVector4D BBVertexBufferObject::getColor(int index)
{
    return QVector4D(m_pVertexes[index].m_fColor[0], m_pVertexes[index].m_fColor[1], m_pVertexes[index].m_fColor[2], m_pVertexes[index].m_fColor[3]);
}

void BBVertexBufferObject::setTexcoord(int index, float u, float v)
{
    m_pVertexes[index].m_fTexcoord[0] = u;
    m_pVertexes[index].m_fTexcoord[1] = v;
    m_pVertexes[index].m_fTexcoord[2] = 0.0f;
    m_pVertexes[index].m_fTexcoord[3] = 0.0f;
}

void BBVertexBufferObject::setTexcoord(int index, const QVector2D &uv)
{
    setTexcoord(index, uv.x(), uv.y());
}

QVector2D BBVertexBufferObject::getTexcoord(int index)
{
    return QVector2D(m_pVertexes[index].m_fTexcoord[0], m_pVertexes[index].m_fTexcoord[1]);
}

void BBVertexBufferObject::computeNormal(unsigned short *pVertexIndexes, int nIndexCount)
{
    // For the time, only triangles with EBO are considered
    for (int i = 0; i < nIndexCount; i += 3)
    {
        int nIndex0 = pVertexIndexes[i];
        int nIndex1 = pVertexIndexes[i + 1];
        int nIndex2 = pVertexIndexes[i + 2];

        QVector3D pos0 = getPosition(nIndex0);
        QVector3D pos1 = getPosition(nIndex1);
        QVector3D pos2 = getPosition(nIndex2);

        QVector3D normal = QVector3D::crossProduct(pos1 - pos0, pos2 - pos0);

        QVector3D normal0 = getNormal(nIndex0);
        QVector3D normal1 = getNormal(nIndex0);
        QVector3D normal2 = getNormal(nIndex0);

        normal0 += normal;
        normal1 += normal;
        normal2 += normal;

        setNormal(nIndex0, normal0);
        setNormal(nIndex1, normal1);
        setNormal(nIndex2, normal2);
    }

    for (int i = 0; i < m_nVertexCount; i++)
    {
        normalizeNormal(i);
    }
}

void BBVertexBufferObject::normalizeNormal(int index)
{
    float x = m_pVertexes[index].m_fNormal[0];
    float y = m_pVertexes[index].m_fNormal[1];
    float z = m_pVertexes[index].m_fNormal[2];
    float mode = sqrtf(x * x + y * y + z * z);
    m_pVertexes[index].m_fNormal[0] = x / mode;
    m_pVertexes[index].m_fNormal[1] = y / mode;
    m_pVertexes[index].m_fNormal[2] = z / mode;
    m_pVertexes[index].m_fNormal[3] = 1.0f;
}

void BBVertexBufferObject::setNormal(int index, float x, float y, float z)
{
    m_pVertexes[index].m_fNormal[0] = x;
    m_pVertexes[index].m_fNormal[1] = y;
    m_pVertexes[index].m_fNormal[2] = z;
    m_pVertexes[index].m_fNormal[3] = 1.0f;
}

void BBVertexBufferObject::setNormal(int index, const QVector3D &normal)
{
    setNormal(index, normal.x(), normal.y(), normal.z());
}

void BBVertexBufferObject::setNormal(int index, const QVector4D &normal)
{
    setNormal(index, normal.x(), normal.y(), normal.z());
}

QVector3D BBVertexBufferObject::getNormal(int index)
{
    return QVector3D(m_pVertexes[index].m_fNormal[0], m_pVertexes[index].m_fNormal[1], m_pVertexes[index].m_fNormal[2]);
}

void BBVertexBufferObject::computeTangent(unsigned short *pVertexIndexes, int nIndexCount)
{
    // For the time, only triangles with EBO are considered
    BB_PROCESS_ERROR_RETURN(pVertexIndexes);

    // record for calculating the average of vertices shared by multiple faces
    // Indicates how many faces the i-th vertex has
    int nFaceCount[m_nVertexCount] = {0};
    QVector3D tangentSum[m_nVertexCount];
    QVector3D bitangentSum[m_nVertexCount];

    for (int i = 0; i < nIndexCount; i += 3)
    {
        int nIndex0 = pVertexIndexes[i];
        int nIndex1 = pVertexIndexes[i + 1];
        int nIndex2 = pVertexIndexes[i + 2];

        QVector3D pos0 = getPosition(nIndex0);
        QVector3D pos1 = getPosition(nIndex1);
        QVector3D pos2 = getPosition(nIndex2);

        QVector2D uv0 = getTexcoord(nIndex0);
        QVector2D uv1 = getTexcoord(nIndex1);
        QVector2D uv2 = getTexcoord(nIndex2);

        QVector3D tangent;
        QVector3D bitangent;
        _computeTangent(nIndex0, pos0, pos1, pos2, uv0, uv1, uv2, tangent, bitangent);
        nFaceCount[nIndex0] ++;
        tangentSum[nIndex0] += tangent;
        bitangentSum[nIndex0] += bitangent;
        _computeTangent(nIndex1, pos1, pos2, pos0, uv1, uv2, uv0, tangent, bitangent);
        nFaceCount[nIndex1] ++;
        tangentSum[nIndex1] += tangent;
        bitangentSum[nIndex1] += bitangent;
        _computeTangent(nIndex2, pos2, pos0, pos1, uv2, uv0, uv1, tangent, bitangent);
        nFaceCount[nIndex2] ++;
        tangentSum[nIndex2] += tangent;
        bitangentSum[nIndex2] += bitangent;
    }

    for (int i = 0; i < m_nVertexCount; i++)
    {
        setTangent(i, tangentSum[i] / nFaceCount[i]);
        setBiTangent(i, bitangentSum[i] / nFaceCount[i]);
    }
}

void BBVertexBufferObject::setTangent(int index, float x, float y, float z, float w)
{
    m_pVertexes[index].m_fTangent[0] = x;
    m_pVertexes[index].m_fTangent[1] = y;
    m_pVertexes[index].m_fTangent[2] = z;
    m_pVertexes[index].m_fTangent[3] = w;
}

void BBVertexBufferObject::setTangent(int index, const QVector3D &tangent)
{
    setTangent(index, tangent.x(), tangent.y(), tangent.z());
}

void BBVertexBufferObject::setBiTangent(int index, float x, float y, float z)
{
    m_pVertexes[index].m_fBiTangent[0] = x;
    m_pVertexes[index].m_fBiTangent[1] = y;
    m_pVertexes[index].m_fBiTangent[2] = z;
    m_pVertexes[index].m_fBiTangent[3] = 1.0f;
}

void BBVertexBufferObject::setBiTangent(int index, const QVector3D &bitangent)
{
    setBiTangent(index, bitangent.x(), bitangent.y(), bitangent.z());
}

QVector3D BBVertexBufferObject::getTangent(int index)
{
    return QVector3D(m_pVertexes[index].m_fTangent[0], m_pVertexes[index].m_fTangent[1], m_pVertexes[index].m_fTangent[2]);
}

QVector3D BBVertexBufferObject::getBiTangent(int index)
{
    return QVector3D(m_pVertexes[index].m_fBiTangent[0], m_pVertexes[index].m_fBiTangent[1], m_pVertexes[index].m_fBiTangent[2]);
}

void BBVertexBufferObject::computeSmoothNormal()
{
    BB_PROCESS_ERROR_RETURN(m_nVertexCount);
    // QList<int> : Save the index of vertices with consistent positions
    // QList<QList<int>> : Save all different positions
    QList<QList<int>> indexGroups;
    // init
    QList<int> group0;
    group0.append(0);
    indexGroups.append(group0);
    // start from 1
    for (int i = 1; i < m_nVertexCount; i++)
    {
        QVector3D pos = getPosition(i);
        int j = 0;
        for (; j < indexGroups.size(); j++)
        {
            QList<int> group = indexGroups.at(j);
            QVector3D center = getPosition(group.at(0));
            // If it is adjacent to the vertex represented by the index 0, the index will be saved in the same group.
            // Otherwise, continue to compare the index 0 of the next group
            if (pos.distanceToPoint(center) < 0.001f)
            {
                indexGroups[j].append(i);
                break;
            }
        }
        if (j >= indexGroups.size())
        {
            // If no vertex close to the current vertex position is found, the current vertex position is regarded as a new group
            QList<int> group;
            group.append(i);
            indexGroups.append(group);
        }
    }
    // For each set of vertices, find the average of their normal
    for (int i = 0; i < indexGroups.size(); i++)
    {
        QList<int> group = indexGroups.at(i);
        QVector3D normal(0, 0, 0);
        for (int j = 0; j < group.size(); j++)
        {
            normal += getNormal(group.at(j));
        }
        normal.normalize();
        // set for each vertex
        for (int j = 0; j < group.size(); j++)
        {
            setSmoothNormal(group.at(j), normal);
        }
    }
}

void BBVertexBufferObject::setSmoothNormal(int index, float x, float y, float z)
{
    m_pVertexes[index].m_fSmoothNormal[0] = x;
    m_pVertexes[index].m_fSmoothNormal[1] = y;
    m_pVertexes[index].m_fSmoothNormal[2] = z;
    m_pVertexes[index].m_fSmoothNormal[3] = 1.0f;
}

void BBVertexBufferObject::setSmoothNormal(int index, const QVector3D &normal)
{
    setSmoothNormal(index, normal.x(), normal.y(), normal.z());
}

QVector3D BBVertexBufferObject::getSmoothNormal(int index)
{
    return QVector3D(m_pVertexes[index].m_fSmoothNormal[0], m_pVertexes[index].m_fSmoothNormal[1], m_pVertexes[index].m_fSmoothNormal[2]);
}

void BBVertexBufferObject::submitData()
{
    updateData(m_BufferType, sizeof(BBVertex) * m_nVertexCount, m_pVertexes);
}

void BBVertexBufferObject::draw(GLenum eDrawPrimitiveType, int nDrawStartIndex, int nDrawCount)
{
    glDrawArrays(eDrawPrimitiveType, nDrawStartIndex, nDrawCount);
}

void BBVertexBufferObject::setSize(int nVertexCount, GLenum hint)
{
    m_nVertexCount = nVertexCount;
    m_pVertexes = new BBVertex[m_nVertexCount];
    memset(m_pVertexes, 0, sizeof(BBVertex) * m_nVertexCount);
    m_Name = createBufferObject(m_BufferType, sizeof(BBVertex) * m_nVertexCount, hint, NULL);
}

void BBVertexBufferObject::_computeTangent(int nVertexIndex,
                                           const QVector3D &pos0, const QVector3D &pos1, const QVector3D &pos2,
                                           const QVector2D &uv0, const QVector2D &uv1, const QVector2D &uv2,
                                           QVector3D &tangent, QVector3D &bitangent)
{
    QVector3D e0 = pos1 - pos0;
    QVector3D e1 = pos2 - pos0;
    QVector2D deltaUV0 = uv1 - uv0;
    QVector2D deltaUV1 = uv2 - uv0;

    float f = 1.0f / (deltaUV0.x() * deltaUV1.y() - deltaUV1.x() * deltaUV0.y());
    tangent.setX(f * (deltaUV1.y() * e0.x() - deltaUV0.y() * e1.x()));
    tangent.setY(f * (deltaUV1.y() * e0.y() - deltaUV0.y() * e1.y()));
    tangent.setZ(f * (deltaUV1.y() * e0.z() - deltaUV0.y() * e1.z()));
    tangent.normalize();
    bitangent.setX(f * (-deltaUV1.x() * e0.x() + deltaUV0.x() * e1.x()));
    bitangent.setY(f * (-deltaUV1.x() * e0.y() + deltaUV0.x() * e1.y()));
    bitangent.setZ(f * (-deltaUV1.x() * e0.z() + deltaUV0.x() * e1.z()));
    bitangent.normalize();
}

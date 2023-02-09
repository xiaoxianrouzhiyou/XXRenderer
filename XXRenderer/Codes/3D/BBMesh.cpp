#include "BBMesh.h"
#include "Renderer/BBVertexBufferObject.h"
#include "Renderer/BBElementBufferObject.h"
#include "Renderer/BBRenderPass.h"
#include "Renderer/BBDrawCall.h"
#include <sstream>

BBMesh::BBMesh()
    : BBMesh(0, 0, 0, 0, 0, 0, 1, 1, 1)
{

}

BBMesh::BBMesh(float px, float py, float pz,
               float rx, float ry, float rz,
               float sx, float sy, float sz)
    : BBRenderableObject(px, py, pz, rx, ry, rz, sx, sy, sz)
{
    m_eDrawPrimitiveType = GL_TRIANGLES;
}

BBMesh::~BBMesh()
{

}

void BBMesh::initByMeshFilePath(const QString &path)
{
    QList<QVector4D> positions;
    load(path, positions);
//    m_pVBO->computeTangent(m_pIndexes, m_nIndexCount);
//    m_pVBO->computeSmoothNormal();

    // create bounding box
    // TO DO

    m_pCurrentMaterial->initMultiPass("standard", BB_PATH_RESOURCE_SHADER(diffuse.vert), BB_PATH_RESOURCE_SHADER(diffuse.frag));
    m_pCurrentMaterial->getAdditiveRenderPass()->setBlendState(true);
    // default
    float *pLightPosition = new float[4] {0.8f, 1.0f, 0.5f, 0.0f};
    float *pLightColor = new float[4] {1.0f, 1.0f, 1.0f, 1.0f};
    m_pCurrentMaterial->setVector4(LOCATION_LIGHT_POSITION, pLightPosition);
    m_pCurrentMaterial->setVector4(LOCATION_LIGHT_COLOR, pLightColor);

    BBRenderableObject::init();

    BBDrawCall *pDrawCall = new BBDrawCall;
    pDrawCall->setMaterial(m_pCurrentMaterial);
    pDrawCall->setVBO(m_pVBO);
    pDrawCall->setEBO(m_pEBO, GL_TRIANGLES, m_nIndexCount, 0);
    appendDrawCall(pDrawCall);
}

void BBMesh::load(const QString &path, QList<QVector4D> &outPositions)
{
    struct VertexDefine
    {
        int posIndex;
        int texcoordIndex;
        int normalIndex;
    };

    int fileSize = 0;
    char *pFileContent = BBUtils::loadFileContent(path.toStdString().c_str(), fileSize);
    if (pFileContent == NULL)
    {
        return;
    }

    // in the file, v... refers to vertex, f... refers to drawing instructions (How to organize the vertices)
    QList<QVector4D> positions, texcoords, normals;
    std::vector<VertexDefine> vertexes;
    std::vector<int> triangleIndexes;
    std::vector<int> quadIndexes;
    std::stringstream ssFileContent(pFileContent);
    std::string temp;
    char oneLine[256];
    while (!ssFileContent.eof())
    {
        memset(oneLine, 0, 256);
        ssFileContent.getline(oneLine, 256);
        // there are empty lines
        if (strlen(oneLine) > 0)
        {
            if (oneLine[0] == 'v')
            {
                // push a row of data into the stream
                // output from stream until space
                std::stringstream ssOneLine(oneLine);
                if (oneLine[1] == 't')
                {
                    // texcoord
                    ssOneLine >> temp; // vt...
                    float u, v;
                    // uv coordinate
                    ssOneLine >> u;
                    ssOneLine >> v;
                    // Put in the container
                    texcoords.append(QVector4D(u, v, 0, 0));
                }
                else if (oneLine[1] == 'n')
                {
                    // normal
                    ssOneLine >> temp;
                    float x, y, z;
                    ssOneLine >> x;
                    ssOneLine >> y;
                    ssOneLine >> z;
                    normals.append(QVector4D(x, y, z, 1.0));
                }
                else
                {
                    // vertex position
                    ssOneLine >> temp;
                    float x, y, z;
                    ssOneLine >> x;
                    ssOneLine >> y;
                    ssOneLine >> z;
                    positions.append(QVector4D(x, y, z, 1.0));
                }
            }
            else if (oneLine[0] == 'f')
            {
                // face, What points are made of each face
                GLenum primitiveType = GL_QUADS;
                std::vector<int> primitiveIndexes;
                std::stringstream ssOneLine(oneLine);
                ssOneLine >> temp; // f...
                // Triangle, 3 pieces of data per line, separated by spaces
                for (int i = 0; i < 4; i++)
                {
                    std::string vertexStr;
                    ssOneLine >> vertexStr;
                    if (vertexStr.length() == 0)
                    {
                        // test
                        primitiveType = GL_TRIANGLES;
                        break;
                    }
                    // The index value of pos and tex of each point, separated by /
                    size_t pos = vertexStr.find_first_of('/');
                    std::string posIndexStr = vertexStr.substr(0, pos);
                    size_t pos2 = vertexStr.find_first_of('/', pos + 1);
                    std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - pos - 1);
                    std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);
                    VertexDefine vd;
                    // string to int
                    vd.posIndex = atoi(posIndexStr.c_str());
                    vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
                    vd.normalIndex = atoi(normalIndexStr.c_str());
                    // Check if it is a duplicate point. The same position, different normals, different points
                    int currentVertexIndex = -1;
                    int currentVertexCount = (int)vertexes.size();
                    for (int j = 0; j < currentVertexCount; j++)
                    {
                        if (vertexes[j].posIndex == vd.posIndex
                                && vertexes[j].normalIndex == vd.normalIndex
                                && vertexes[j].texcoordIndex == vd.texcoordIndex)
                        {
                            currentVertexIndex = j;
                            break;
                        }
                    }
                    // If the point does not exist, add the point container
                    if (currentVertexIndex == -1)
                    {
                        currentVertexIndex = (int)vertexes.size();
                        vertexes.push_back(vd);
                    }
                    // Regardless of whether it exists, record the index value of the point in the point container
                    primitiveIndexes.push_back(currentVertexIndex);
                }
                // Primitiveindexes store the vertex index of a primitive.
                // Judge the type of primitive according to the number of vertices,
                // and then push it to the total index table of the corresponding primitive
                if (primitiveType == GL_TRIANGLES)
                {
                    triangleIndexes.push_back(primitiveIndexes[0]);
                    triangleIndexes.push_back(primitiveIndexes[1]);
                    triangleIndexes.push_back(primitiveIndexes[2]);
                }
                else if (primitiveType == GL_QUADS)
                {
                    quadIndexes.push_back(primitiveIndexes[0]);
                    quadIndexes.push_back(primitiveIndexes[1]);
                    quadIndexes.push_back(primitiveIndexes[2]);
                    quadIndexes.push_back(primitiveIndexes[3]);
                }
            }
        }
    }

    m_nIndexCount = (int)triangleIndexes.size();
    m_pIndexes = new unsigned short[m_nIndexCount];
    for (int i = 0; i < m_nIndexCount; i++)
    {
        m_pIndexes[i] = triangleIndexes[i];
    }

    // How many unique points
    m_nVertexCount = (int)vertexes.size();
    m_pVBO = new BBVertexBufferObject(m_nVertexCount);
    for (int i = 0; i < m_nVertexCount; i++)
    {
        // vertexes[i].posIndex - 1
        // The index starts from 1 in .obj
        QVector4D temp;

        temp = positions.at(vertexes[i].posIndex - 1);
        m_pVBO->setPosition(i, temp);

        m_pVBO->setColor(i, m_DefaultColor);

        temp = texcoords.at(vertexes[i].texcoordIndex - 1);
        m_pVBO->setTexcoord(i, temp.x(), temp.y());

        temp = normals.at(vertexes[i].normalIndex - 1);
        m_pVBO->setNormal(i, temp);
    }

    // for creating bounding box
    outPositions = positions;

    BB_SAFE_DELETE(pFileContent);
}

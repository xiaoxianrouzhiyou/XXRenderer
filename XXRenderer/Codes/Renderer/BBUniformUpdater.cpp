#include "BBUniformUpdater.h"
#include "BBCamera.h"
#include <QDateTime>

BBUniformUpdater::BBUniformUpdater(GLint location, const BBUpdateUniformFunc &updateFunc, BBMaterialProperty *pTargetProperty)
    : BBBaseRenderComponent()
{
    m_Location = location;
    m_UpdateUniformFunc = updateFunc;
    m_pTargetProperty = pTargetProperty;
    m_LastTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

BBUniformUpdater::~BBUniformUpdater()
{
    BB_SAFE_DELETE(m_pTargetProperty);
}

BBUniformUpdater* BBUniformUpdater::clone()
{
    return new BBUniformUpdater(m_Location, m_UpdateUniformFunc,
                                m_pTargetProperty == nullptr ? nullptr : m_pTargetProperty->clone());
}

void BBUniformUpdater::updateUniform(GLint location, void *pUserData, void *pPropertyValue)
{
    (this->*m_UpdateUniformFunc)(location, pUserData, pPropertyValue);
}

void BBUniformUpdater::updateCameraProjectionMatrix(GLint location, void *pCamera, void *pPropertyValue)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, ((BBCamera*)pCamera)->getProjectionMatrix().data());
}

void BBUniformUpdater::updateCameraInverseProjectionMatrix(GLint location, void *pCamera, void *pPropertyValue)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, ((BBCamera*)pCamera)->getProjectionMatrix().inverted().data());
}

void BBUniformUpdater::updateCameraViewMatrix(GLint location, void *pCamera, void *pPropertyValue)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, ((BBCamera*)pCamera)->getViewMatrix().data());
}

void BBUniformUpdater::updateCameraInverseViewMatrix(GLint location, void *pCamera, void *pPropertyValue)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, ((BBCamera*)pCamera)->getViewMatrix().inverted().data());
}

void BBUniformUpdater::updateCameraPosition(GLint location, void *pCamera, void *pPropertyValue)
{
    QVector3D position = ((BBCamera*)pCamera)->getPosition();
    glUniform4f(location, position.x(), position.y(), position.z(), 1.0f);
}

//void BBUniformUpdater::updateCanvas(GLint location, void *pCanvas, void *pPropertyValue)
//{
//    glUniform4fv(location, 1, ((BBCanvas*)pCanvas)->getUniformInfo());
//}

void BBUniformUpdater::updateCameraParameters0(GLint location, void *pCamera, void *pPropertyValue)
{
    glUniform4fv(location, 1, ((BBCamera*)pCamera)->getCameraParameters0());
}

void BBUniformUpdater::updateCameraParameters1(GLint location, void *pCamera, void *pPropertyValue)
{
    glUniform4fv(location, 1, ((BBCamera*)pCamera)->getCameraParameters1());
}

void BBUniformUpdater::updateTime(GLint location, void *pUserData, void *pPropertyValue)
{
    qint64 currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    float fDelta = currentTime - m_LastTime;
    float *ptr = new float[4] {fDelta, currentTime, currentTime % 100000000, 0.0};
    glUniform4fv(location, 1, ptr);
    m_LastTime = currentTime;
}

void BBUniformUpdater::updateFloat(GLint location, void *pCamera, void *pPropertyValue)
{
    BBFloatMaterialProperty *pProperty = (BBFloatMaterialProperty*)pPropertyValue;
    glUniform1f(location, pProperty->getPropertyValue());
}

void BBUniformUpdater::updateFloatArray(GLint location, void *pCamera, void *pPropertyValue)
{
    BBFloatArrayMaterialProperty *pProperty = (BBFloatArrayMaterialProperty*)pPropertyValue;
    glUniform1fv(location, pProperty->getArrayCount(), pProperty->getPropertyValue());
}

void BBUniformUpdater::updateMatrix4(GLint location, void *pCamera, void *pPropertyValue)
{
    BBMatrix4MaterialProperty *pProperty = (BBMatrix4MaterialProperty*)pPropertyValue;
    glUniformMatrix4fv(location, 1, GL_FALSE, pProperty->getPropertyValue());
}

void BBUniformUpdater::updateVector4(GLint location, void *pCamera, void *pPropertyValue)
{
    BBVector4MaterialProperty *pProperty = (BBVector4MaterialProperty*)pPropertyValue;
    glUniform4fv(location, 1, pProperty->getPropertyValue());
}

void BBUniformUpdater::updateVector4Array(GLint location, void *pCamera, void *pPropertyValue)
{
    BBVector4ArrayMaterialProperty *pProperty = (BBVector4ArrayMaterialProperty*)pPropertyValue;
    glUniform4fv(location, pProperty->getArrayCount(), pProperty->getPropertyValue());
}

void BBUniformUpdater::updateSampler2D(GLint location, void *pCamera, void *pPropertyValue)
{
    BBSampler2DMaterialProperty *pProperty = (BBSampler2DMaterialProperty*)pPropertyValue;
    int nSlotIndex = pProperty->getSlotIndex();
    glActiveTexture(GL_TEXTURE0 + nSlotIndex);
    glBindTexture(GL_TEXTURE_2D, pProperty->getTextureName());
    glUniform1i(location, nSlotIndex);
}

void BBUniformUpdater::updateSampler3D(GLint location, void *pCamera, void *pPropertyValue)
{
    BBSampler3DMaterialProperty *pProperty = (BBSampler3DMaterialProperty*)pPropertyValue;
    int nSlotIndex = pProperty->getSlotIndex();
    glActiveTexture(GL_TEXTURE0 + nSlotIndex);
    glBindTexture(GL_TEXTURE_3D, pProperty->getTextureName());
    glUniform1i(location, nSlotIndex);
}

void BBUniformUpdater::updateSamplerCube(GLint location, void *pCamera, void *pPropertyValue)
{
    BBSamplerCubeMaterialProperty *pProperty = (BBSamplerCubeMaterialProperty*)pPropertyValue;
    int nSlotIndex = pProperty->getSlotIndex();
    glActiveTexture(GL_TEXTURE0 + nSlotIndex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, pProperty->getTextureName());
    glUniform1i(location, nSlotIndex);
}

#-------------------------------------------------
#
# Project created by QtCreator 2023-02-06T22:42:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XXRenderer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Codes/Base/BBObject.cpp \
    Codes/Base/BBRenderableObject.cpp \
    Codes/Scene/BBScene.cpp \
    Codes/Utils/BBUtils.cpp \
    Codes/Widgets/BBOpenGLWidget.cpp \
    Codes/2D/BBCanvas.cpp \
    Codes/Renderer/BBCamera.cpp \
    Codes/Renderer/BBDrawCall.cpp \
    Codes/Utils/BBLinkedList.cpp \
    Codes/Renderer/BBMaterial.cpp \
    Codes/Renderer/BBRenderPass.cpp \
    Codes/Renderer/BBRenderState.cpp \
    Codes/Renderer/BBUniformUpdater.cpp \
    Codes/Renderer/BBMaterialProperty.cpp \
    Codes/Renderer/BBElementBufferObject.cpp \
    Codes/Renderer/BBBufferObject.cpp \
    Codes/Renderer/BBVertexBufferObject.cpp \
    Codes/Renderer/BBAttribute.cpp \
    Codes/Geometry/BBRay.cpp \
    Codes/3D/BBModel.cpp \
    Codes/3D/BBMesh.cpp \
    Codes/Math/BBMath.cpp \
    Codes/Renderer/Shader/BBBaseShader.cpp \
    Codes/Renderer/Shader/BBShader.cpp

HEADERS += \
        mainwindow.h \
    Codes/Base/BBObject.h \
    Codes/Base/BBRenderableObject.h \
    Codes/Scene/BBScene.h \
    Codes/Utils/BBUtils.h \
    Codes/Widgets/BBOpenGLWidget.h \
    Codes/2D/BBCanvas.h \
    Codes/Renderer/BBCamera.h \
    Codes/Renderer/BBBaseRenderComponent.h \
    Codes/Renderer/BBDrawCall.h \
    Codes/Utils/BBLinkedList.h \
    Codes/Renderer/BBMaterial.h \
    Codes/Renderer/BBRenderPass.h \
    Codes/Renderer/BBRenderState.h \
    Codes/Renderer/BBUniformUpdater.h \
    Codes/Renderer/BBMaterialProperty.h \
    Codes/Renderer/BBElementBufferObject.h \
    Codes/Renderer/BBBufferObject.h \
    Codes/Renderer/BBVertexBufferObject.h \
    Codes/Renderer/BBAttribute.h \
    Codes/Geometry/BBRay.h \
    Codes/3D/BBModel.h \
    Codes/3D/BBMesh.h \
    Codes/Math/BBMath.h \
    Codes/Renderer/Shader/BBBaseShader.h \
    Codes/Renderer/Shader/BBShader.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += \
    ../XXRenderer/Codes \

LIBS += -lopengl32 -lglu32 -lglut

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#ifndef BBOPENGLWIDGET_H
#define BBOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class BBScene;
class BBOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit BBOpenGLWidget(QWidget *parent = nullptr);
    ~BBOpenGLWidget() override;

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

private:
    BBScene *m_pScene;

signals:

public slots:
};

#endif // BBOPENGLWIDGET_H

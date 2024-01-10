#ifndef MYPICTUREWIDGET_H
#define MYPICTUREWIDGET_H

#include <QLabel>
#include <QRect>
#include <QPixmap>
#include <QResizeEvent>
#include <QWidget>
#include <QOpenGLWidget>

#pragma execution_character_set("utf-8") //防止中文乱码

class MyPictureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyPictureWidget(QWidget *parent = nullptr);
    ~MyPictureWidget() override;
    void SetPicturePixmap( QPixmap &pixmap,int index);

signals:
    void sigUpdate();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    Q_DISABLE_COPY(MyPictureWidget)
    QPixmap m_pixmap;
    /*double des_w_h_ratio;
    double src_w_h_ratio;
    int scale_w;
    int scale_h;*/
    int _index;


};

#endif // MYPICTUREWIDGET_H

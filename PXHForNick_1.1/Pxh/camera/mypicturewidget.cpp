#include "mypicturewidget.h"
#include <QPainter>
#include <QDebug>
#include <QThread>
#include <QApplication>
#include <QEvent>
MyPictureWidget::MyPictureWidget(QWidget *parent) : QWidget(parent)
{
    //通过信号槽的刷新要注意槽的最后一个参数，需要使用 Qt::QueuedConnection，
    //这里当控制权回到被调用线程的时候会进行刷新，刷新过程会在当前线程执行完成后进行.
    connect(this, &MyPictureWidget::sigUpdate, this, [this]() {
        this->update();//在GUI线程中执行update
    }, Qt::QueuedConnection);
}

MyPictureWidget::~MyPictureWidget()
{
}

void MyPictureWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
   // des_w_h_ratio= static_cast<double>(this->width()) / static_cast<double>(this->height());
    update();
}

void MyPictureWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    if(m_pixmap.isNull())
    {
        painter.fillRect(this->rect(), QColor(40, 40, 40));
    }
    else
    {
        /*  int des_h = this->height();
        int des_w = this->width();
        if(des_w_h_ratio >= src_w_h_ratio)
        {
            scale_h = des_h;
            scale_w = static_cast<int>(src_w_h_ratio * des_h);
        } else
        {
            scale_w = des_w;
            scale_h = static_cast<int>(des_w / src_w_h_ratio);
        }
        qDebug()<<"drawPixmap before "<<_index;
        QPixmap temp_pixmap = m_pixmap.scaled(scale_w, scale_h);*/

        QRect draw_rect = this->rect();

        /*int adjust_pos_h = des_h - temp_pixmap.height();
        int adjust_pos_w = des_w - temp_pixmap.width();
        draw_rect.adjust(adjust_pos_w/2, adjust_pos_h/2, -adjust_pos_w/2, -adjust_pos_h/2);
        painter.fillRect(this->rect(), Qt::black);
        painter.drawPixmap(draw_rect, temp_pixmap);*/
        painter.drawPixmap(draw_rect, m_pixmap);
    }
    painter.end();
}

void MyPictureWidget::SetPicturePixmap( QPixmap &pixmap,int index)
{
    m_pixmap =pixmap;
    _index=index;
    // src_w_h_ratio = static_cast<double>(m_pixmap.width()) / static_cast<double>(m_pixmap.height());
    //  update();//需要在主线程中发送信号
}



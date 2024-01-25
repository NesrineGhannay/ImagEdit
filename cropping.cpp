#include "cropping.h"

#include <QLabel>
#include <QPainter>
#include <iostream>

static constexpr int resizeHandleWidth = 10;

Cropping::Cropping(QWidget *parent, const QRect &rect)
    : QLabel(parent),
    currentRect(rect)
{
    currentRect = currentRect;;
    m_resizeHandlePressed = false;
}


QRect Cropping::resizeHandle() const
{
    QPoint br = currentRect.bottomRight();
    return QRect(br - QPoint(resizeHandleWidth, resizeHandleWidth), br);
}


void Cropping::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    m_resizeHandlePressed = this->resizeHandle().contains(event->position().toPoint());
    if (m_resizeHandlePressed)
        m_mousePressOffset = currentRect.bottomRight() - event->position().toPoint();
    else
        m_mousePressOffset = event->position().toPoint() - currentRect.topLeft();


}

void Cropping::mouseReleaseEvent(QMouseEvent *event)
{


    this->setPixmap(cutImage());

    update();
    event->accept();
    m_resizeHandlePressed = false;
}

QPixmap Cropping::cutImage() {
    QImage image = this->pixmap().toImage();
    //this->pixmap().toImage().setPixel(10, 10, qRgb(255, 255, 255));
    for(int i = 0; i < currentRect.topLeft().x(); i++) {
        for(int j = 0; j < image.height(); j++) {
            image.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.topRight().x(); i < image.width(); i++) {
        for(int j = 0; j < image.height(); j++) {
            image.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.topLeft().x(); i <  currentRect.topRight().x(); i++) {
        for(int j = 0; j < currentRect.topLeft().y(); j++) {
            image.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.bottomLeft().x(); i < currentRect.bottomRight().x(); i++) {
        for(int j = currentRect.bottomLeft().y(); j < image.height(); j++) {
            image.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    return QPixmap::fromImage(image);
}

void Cropping::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    if (m_resizeHandlePressed) {
        currentRect = QRect(currentRect.topLeft(), event->position().toPoint() + m_mousePressOffset);

    } else {
        currentRect.moveTopLeft(event->position().toPoint() - m_mousePressOffset);
    }
    update();


}

void Cropping::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue, 2));
    QColor grayWithAlpha = QColor(0, 0, 128, 128);
    painter.setBrush(QBrush(grayWithAlpha));
    painter.drawRect(currentRect);
    painter.drawRect(resizeHandle());
}

void Cropping::drawRectCropping(QPixmap *pix) {
    currentRect = QRect(0,10, this->width()-10, this->height()-10);
    update();
}


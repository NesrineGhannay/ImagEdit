#include "cropping.h"

#include <QLabel>
#include <QPainter>
#include <iostream>

static constexpr int resizeHandleWidth = 40;

Cropping::Cropping(QWidget *parent, const QRect &rect)
    : QLabel(parent),
    currentRect(rect)
{
    currentRect = currentRect;;
    m_resizeHandlePressed = false;
    setFocusPolicy(Qt::StrongFocus);

}


QRect Cropping::resizeHandle() const
{
    QPoint br = currentRect.bottomRight();
    return QRect(br - QPoint(resizeHandleWidth, resizeHandleWidth), br);
}

void Cropping::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Return)
        this->setPixmap(cutImage());

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
    update();
    event->accept();
    m_resizeHandlePressed = false;
}

QPixmap Cropping::cutImage() {
    QImage newImage = pixImage.toImage();

    int marge_lateral = (this->width() - newImage.width())/2;
    int marge_vertical = (this->height() - newImage.height())/2;

    for(int i = 0; i < currentRect.left()-marge_lateral; i++) {
        for(int j = 0; j < newImage.height(); j++) {
            newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.right()-marge_lateral; i < newImage.width(); i++) {
        for(int j = 0; j < newImage.height(); j++) {
            newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.topLeft().x() - marge_lateral; i < currentRect.width() + marge_lateral; i++) {
        for(int j = 0; j < currentRect.topLeft().y() - marge_vertical; j++) {
            newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.bottomLeft().x() - marge_lateral; i < currentRect.width() + marge_lateral; i++) {
        for(int j = currentRect.bottomLeft().y() - marge_vertical; j < newImage.height(); j++) {
            newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }


    return QPixmap::fromImage(newImage);
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
    pixImage = *pix;
    currentRect = QRect(this->width()/2-pix->width()/2,
                        this->height()/2-pix->height()/2,
                        pix->width(),
                        pix->height()
                        );
    update();
    releaseKeyboard();

}


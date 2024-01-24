#include "cropping.h"

#include <QLabel>
#include <QPainter>

static constexpr int resizeHandleWidth = 10;

Cropping::Cropping(QWidget *parent, const QRect &rect)
    : QLabel(parent),
    currentRect(rect)
{
    currentRect = currentRect;;
    m_resizeHandlePressed = false;
}

void Cropping::display() {
    QLabel *label = new QLabel(this);

    //connect(this, Cropping::currentRect, this, Cropping::mousePressEvent);
    //gridLayout->addWidget(label);
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
    event->accept();
    m_resizeHandlePressed = false;
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
    //QSize size = rect->size().expandedTo(Shape::minSize);
    //rect.setSize(size);


}

void Cropping::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue, 2));
    QColor grayWithAlpha = QColor(128, 128, 128, 128);  // Adjust the alpha value as needed
    painter.setBrush(QBrush(grayWithAlpha));
    painter.drawRect(currentRect);
    painter.drawRect(resizeHandle());
}


void Cropping::drawRectCropping(QPixmap *pix) {
    currentRect = QRect(0, 0,  pix->width(),  pix->height());
    update();
}



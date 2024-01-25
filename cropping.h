#ifndef CROPPING_H
#define CROPPING_H

#include <QLabel>
#include <QPaintEvent>
#include <QMouseEvent>

using namespace std;

class Cropping : public QLabel
{
    Q_OBJECT

public:
    explicit Cropping(QWidget *parent = nullptr, const QRect &rect = QRect());
    void drawRectCropping(QPixmap *pix);
    
    void cropRect(QPixmap *pix);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;


private:
    QRect resizeHandle() const;
    bool m_resizeHandlePressed = false;
    QPoint m_mousePressOffset;
    int m_mousePressIndex = -1;
    QRect currentRect;
    bool isCropping = false;
    QPixmap cutImage();
    QPixmap pixImage;
    QPixmap rectToPixmap(const QRect &rect);

};

#endif // CROPPING_H

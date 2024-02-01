#ifndef SELECTIONAREA_H
#define SELECTIONAREA_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class selectionarea;
}

class selectionarea : public QWidget
{
    Q_OBJECT

private slots:
    void on_pushButton_clicked();


public:
    explicit selectionarea(QWidget *parent = nullptr);
    ~selectionarea();

    bool getIsFilter();
    void setIsFilter(bool selectBool);
    /*//Partie copié pour rectangle
    void drawRectSelect(QPixmap *pix);
    void deleteRectSelect();
    bool getIsSelect();
    QPixmap getPixmap();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void selectPicture();
    //Fin partie copié*/

private:
    Ui::selectionarea *ui;

    /*QPixmap *pix;
    selectionarea *actualSelection;

    QRect resizeHandle() const;
    bool m_resizeHandlePressed = false;
    QPoint m_mousePressOffset;
    int m_mousePressIndex = -1;
    QRect currentRect;
    bool isCropping = false;
    QPixmap cutImage();
    QPixmap pixImage;
    QPixmap rectToPixmap(const QRect &rect);*/

    QLabel *labelSelected;
    QImage originalImage;
    bool isSelect = false;

    void updateUIForCurrentTool();
    void selectRectangle();
    void selectEllipse();
    void selectStar();
    void selectTriangle();
    void selectLibre();

    QPixmap getSelectedImage() const;
};

#endif // SELECTIONAREA_H

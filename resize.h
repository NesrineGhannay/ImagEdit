#ifndef RESIZE_H
#define RESIZE_H

#include <QWidget>
#include "cropping.h"

namespace Ui {
class Resize;
}

class Resize : public QWidget
{
    Q_OBJECT

public:
    explicit Resize(QWidget *parent = nullptr);
    ~Resize();

    void setCropping(Cropping *cropping);  // Ajout du setter

private slots:
    void on_four_three_clicked();
    void on_widthSpinBox_valueChanged(int arg1);
    void on_heightSpinBox_valueChanged(int arg1);

private:
    Ui::Resize *ui;
    Cropping *actualCropping;
    int *height;
    int *width;
};

#endif // RESIZE_H

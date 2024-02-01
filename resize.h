// resize.h
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
    void on_pushButton_clicked();

private:
    Ui::Resize *ui;
    Cropping *actualCropping;
};

#endif // RESIZE_H

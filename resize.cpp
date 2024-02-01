// resize.cpp
#include "resize.h"
#include "ui_resize.h"
#include "cropping.h"

Resize::Resize(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Resize)
{
    height = new int;
    width = new int;
    ui->setupUi(this);
}

Resize::~Resize()
{
    delete ui;
}

void Resize::setIsResize(bool resizeBool) {
    isResize = resizeBool;
}

bool Resize::getIsResize() {
    return isResize;
}

void Resize::setCropping(Cropping *cropping)
{
    actualCropping = cropping;
    *height = actualCropping->height();
    *width = actualCropping->width();
    ui->heightSpinBox->setValue(*height);
    ui->widthSpinBox->setValue(*width);
}

void Resize::on_four_three_clicked()
{
    QPixmap currentPixmap = actualCropping->getPixmap();

    if (!currentPixmap.isNull()) {
        QPixmap resizedPixmap = currentPixmap.scaled((actualCropping->height() * 4) / 3, actualCropping->height(), Qt::KeepAspectRatio);
        actualCropping->setPixmap(resizedPixmap);
        actualCropping->update();
    }
}

void Resize::on_widthSpinBox_valueChanged(int arg1)
{
    QPixmap currentPixmap = actualCropping->getPixmap();

    if (!currentPixmap.isNull()) {
        QPixmap resizedPixmap = currentPixmap.scaled(arg1, *height, Qt::KeepAspectRatio);
        actualCropping->setPixmap(resizedPixmap);
        actualCropping->update();
    }
}

void Resize::on_heightSpinBox_valueChanged(int arg1)
{
    *height = arg1;
    QPixmap currentPixmap = actualCropping->getPixmap();

    if (!currentPixmap.isNull()) {
        QPixmap resizedPixmap = currentPixmap.scaled(*width, arg1, Qt::KeepAspectRatio);
        actualCropping->setPixmap(resizedPixmap);
        actualCropping->update();
    }
}



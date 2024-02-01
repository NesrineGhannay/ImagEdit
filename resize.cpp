// resize.cpp
#include "resize.h"
#include "ui_resize.h"
#include "cropping.h"

Resize::Resize(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Resize)
{
    ui->setupUi(this);
}

Resize::~Resize()
{
    delete ui;
}

void Resize::setCropping(Cropping *cropping)
{
    actualCropping = cropping;
}


void Resize::on_pushButton_clicked()
{
    QPixmap currentPixmap = actualCropping->getPixmap();

    if (!currentPixmap.isNull()) {
        QPixmap resizedPixmap = currentPixmap.scaled(25, 25, Qt::KeepAspectRatio);
        actualCropping->setPixmap(resizedPixmap);
        actualCropping->update();
    }
}

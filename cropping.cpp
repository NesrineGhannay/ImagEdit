#include "cropping.h"

#include <QLabel>

Cropping::Cropping(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

}

void Cropping::display() {
    QLabel *label = new QLabel(this);


    gridLayout->addWidget(label);
}

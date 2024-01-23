#ifndef CROPPING_H
#define CROPPING_H

#include "ui_cropping.h"

class Cropping : public QWidget, private Ui::Cropping
{
    Q_OBJECT

public:
    explicit Cropping(QWidget *parent = nullptr);

public:
    void display();

};


#endif // CROPPING_H

#include "rognerarea.h"
#include "ui_rognerarea.h"

RognerArea::RognerArea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RognerArea)
{
    ui->setupUi(this);
}

RognerArea::~RognerArea()
{
    delete ui;
}

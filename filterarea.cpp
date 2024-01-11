#include "filterarea.h"
#include "ui_filterarea.h"

FilterArea::FilterArea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FilterArea)
{
    ui->setupUi(this);
}

FilterArea::~FilterArea()
{
    delete ui;
}

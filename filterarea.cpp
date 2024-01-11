#include "filterarea.h"
#include "ui_filterarea.h"

Filterarea::Filterarea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Filterarea)
{
    ui->setupUi(this);
}

Filterarea::~Filterarea()
{
    delete ui;
}

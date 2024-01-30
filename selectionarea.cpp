#include "selectionarea.h"
#include "ui_selectionarea.h"

selectionarea::selectionarea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectionarea)
{
    ui->setupUi(this);
}

selectionarea::~selectionarea()
{
    delete ui;
}

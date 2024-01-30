#include "selectionarea.h"
#include "ui_selectionarea.h"

selectionarea::selectionarea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectionarea)
{
    ui->setupUi(this);
}

void selectionarea::setIsFilter(bool selectBool) {
    isSelect = selectBool;
}

bool selectionarea::getIsFilter() {
    return isSelect;
}

void selectionarea::on_pushButton_clicked()
{
    this->close();
}


selectionarea::~selectionarea()
{
    delete ui;
}

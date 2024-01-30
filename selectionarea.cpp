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

selectionarea::~selectionarea()
{
    delete ui;
}

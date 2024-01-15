#include "selectionaera.h"
#include "ui_selectionaera.h"

selectionaera::selectionaera(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectionaera)
{
    ui->setupUi(this);
}

selectionaera::~selectionaera()
{
    delete ui;
}

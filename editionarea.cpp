#include "editionarea.h"
#include "ui_editionarea.h"

EditionArea::EditionArea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditionArea)
{
    ui->setupUi(this);



}

EditionArea::~EditionArea()
{
    delete ui;
}

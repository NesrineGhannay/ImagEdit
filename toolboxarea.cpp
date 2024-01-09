#include "toolboxarea.h"
#include "ui_toolboxarea.h"

ToolboxArea::ToolboxArea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolboxArea)
{
    ui->setupUi(this);
}

ToolboxArea::~ToolboxArea()
{
    delete ui;
}

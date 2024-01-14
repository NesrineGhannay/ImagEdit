#include "toolboxarea.h"
#include "ui_toolboxarea.h"
#include "filterarea.h"
#include "selectionaera.h"

ToolboxArea::ToolboxArea(QWidget *parent) : QWidget(parent), ui(new Ui::ToolboxArea)
{
    ui->setupUi(this);
}

void ToolboxArea::on_filter_clicked()
{
    FilterArea *filter = new FilterArea();
    filter->show();
}

void ToolboxArea::on_selection_clicked()
{
    selectionaera *selection = new selectionaera();
    selection->show();
}


ToolboxArea::~ToolboxArea()
{
    delete ui;
}




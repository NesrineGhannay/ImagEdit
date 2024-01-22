#include "toolboxarea.h"
#include "ui_toolboxarea.h"
#include "filterarea.h"
#include "selectionaera.h"
#include "rognerarea.h"

#include <iostream>
using namespace std;

ToolboxArea::ToolboxArea(QWidget *parent) : QWidget(parent), ui(new Ui::ToolboxArea)
{
    ui->setupUi(this);
}

void ToolboxArea::on_filter_clicked()
{
    FilterArea *filter = new FilterArea();
    cout << "hello" << endl;
    //filter->setImage();
    filter->show();


}







void ToolboxArea::on_selection_clicked()
{
    selectionaera *selection = new selectionaera();
    selection->show();
}

void ToolboxArea::on_rogner_clicked()
{
    RognerArea *rogner = new RognerArea();
    rogner->show();
}


ToolboxArea::~ToolboxArea()
{
    delete ui;
}




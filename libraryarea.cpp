#include "libraryarea.h"
#include "ui_libraryarea.h"

LibraryArea::LibraryArea(QWidget *parent) : QWidget(parent), ui(new Ui::LibraryArea)
{
    ui->setupUi(this);
}

LibraryArea::~LibraryArea()
{
    delete ui;
}



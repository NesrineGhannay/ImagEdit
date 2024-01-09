#include "imagedit.h"
#include "ui_imagedit.h"

ImagEdit::ImagEdit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImagEdit)
{
    ui->setupUi(this);

    //Instance

    editionarea = new EditionArea();
    libraryarea = new LibraryArea();
    settingarea = new SettingArea();
    toolboxarea = new ToolboxArea();
}

ImagEdit::~ImagEdit()
{
    delete ui;
}

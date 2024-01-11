#include "imagedit.h"
#include "ui_imagedit.h"

ImagEdit::ImagEdit(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImagEdit)
{
    ui->setupUi(this);

    //Instance

    //editionarea = new EditionArea(this);
    //libraryarea = new LibraryArea(this);
    //settingarea = new SettingArea(this);
    //toolboxarea = new ToolboxArea(this);
}

ImagEdit::~ImagEdit()
{
    delete ui;
}

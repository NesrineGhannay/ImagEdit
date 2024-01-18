#include "settingarea.h"
#include "ui_settingarea.h"

SettingArea::SettingArea(QWidget *parent) : QWidget(parent), ui(new Ui::SettingArea)
{
    ui->setupUi(this);


}

SettingArea::~SettingArea()
{
    delete ui;
}



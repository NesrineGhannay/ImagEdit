#ifndef IMAGEDIT_H
#define IMAGEDIT_H

#include <QMainWindow>

#include "editionarea.h"
#include "libraryarea.h"
#include "settingarea.h"
#include "toolboxarea.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ImagEdit;
}
QT_END_NAMESPACE

class ImagEdit : public QMainWindow
{
    Q_OBJECT

public:
    ImagEdit(QWidget *parent = nullptr);
    ~ImagEdit();
    EditionArea *editionarea;
    LibraryArea *libraryarea;
    SettingArea *settingarea;
    ToolboxArea *toolboxarea;



private:
    Ui::ImagEdit *ui;
};
#endif // IMAGEDIT_H

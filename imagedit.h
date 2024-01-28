#ifndef IMAGEDIT_H
#define IMAGEDIT_H

#include <QMainWindow>
#include <QPalette>

#include "libraryarea.h"
#include "settingarea.h"
#include "filterarea.h"
#include "cropping.h"


using namespace std;

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
    LibraryArea *libraryarea;
    SettingArea *settingarea;
    Cropping *croppingarera;
    FilterArea *filterarea;



public slots:
    void displayOnEdition();
    void on_filter_clicked();
    void on_rogner_clicked();


private:
    Ui::ImagEdit *ui;
    QString *path;
    QString *fileName;
    QPixmap *pix;
    QRect *rect;
    Cropping *actualCropping;

    QPushButton *boutonFiltre;
    bool isFilterVisible;
};
#endif // IMAGEDIT_H

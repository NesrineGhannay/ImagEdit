#ifndef SETTINGAREA_H
#define SETTINGAREA_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>
#include <QLabel>

namespace Ui {
class SettingArea;
}

class SettingArea : public QWidget
{
    Q_OBJECT

public:
    explicit SettingArea(QWidget *parent = 0);
    ~SettingArea();

private:
    Ui::SettingArea *ui;
    QString getPicturePath();


private slots:


};
#endif // SETTINGAREA_H

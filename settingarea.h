#ifndef SETTINGAREA_H
#define SETTINGAREA_H

#include <QWidget>

namespace Ui {
class SettingArea;
}

class SettingArea : public QWidget
{
    Q_OBJECT

public:
    explicit SettingArea(QWidget *parent = nullptr);
    ~SettingArea();

private:
    Ui::SettingArea *ui;
};

#endif // SETTINGAREA_H

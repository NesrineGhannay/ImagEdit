#ifndef SETTINGAREA_H
#define SETTINGAREA_H

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>


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
    QPushButton *boutonOuvrir;
    QPushButton *boutonEnregistrer;
    QPushButton *boutonEnregistrerSous;
    QPushButton *boutonAnnuler;

private slots:
    void onBoutonOuvrirClicked();
    void onBoutonEnregistrerClicked();
    void onBoutonEnregistrerSousClicked();
    void onBoutonAnnulerClicked();

};
#endif // SETTINGAREA_H

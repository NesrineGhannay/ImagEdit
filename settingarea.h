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
    QPushButton *boutonOuvrir;
    QPushButton *boutonEnregistrer;
    QPushButton *boutonEnregistrerSous;
    QPushButton *boutonAnnuler;
    QPushButton *boutonRevenirArriere;
    QPushButton *boutonRevenirAvant;
    QPushButton *boutonPlus;
    QPushButton *boutonMoins;
    QPushButton *boutonSupprimer;
    QLabel *logoLabel;




private slots:
    void onBoutonOuvrirClicked();
    void onBoutonEnregistrerClicked();
    void onBoutonEnregistrerSousClicked();
    void onBoutonAnnulerClicked();
    void onBoutonRevenirArriereClicked();
    void onBoutonRevenirAvantClicked();
    void onBoutonPlusClicked();
    void onBoutonMoinsClicked();
    void onBoutonSupprimerClicked();

};
#endif // SETTINGAREA_H

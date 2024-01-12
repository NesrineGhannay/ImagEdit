#include "settingarea.h"
#include "ui_settingarea.h"
#include <QStandardPaths>
//#include "editionarea.h"

SettingArea::SettingArea(QWidget *parent) : QWidget(parent), ui(new Ui::SettingArea)
{
    ui->setupUi(this);

    boutonOuvrir = new QPushButton("Ouvrir", this);
    boutonOuvrir->setGeometry(10, 10, 100, 30);
    connect(boutonOuvrir, &QPushButton::clicked, this, &SettingArea::onBoutonOuvrirClicked);

    boutonEnregistrer = new QPushButton("Enregistrer", this);
    boutonEnregistrer->setGeometry(120, 10, 100, 30);
    connect(boutonEnregistrer, &QPushButton::clicked, this, &SettingArea::onBoutonEnregistrerClicked);

    boutonEnregistrerSous = new QPushButton("Enregistrer sous", this);
    boutonEnregistrerSous->setGeometry(230, 10, 100, 30);
    connect(boutonEnregistrerSous, &QPushButton::clicked, this, &SettingArea::onBoutonEnregistrerSousClicked);

    boutonAnnuler = new QPushButton("Annuler", this);
    boutonAnnuler->setGeometry(340, 10, 100, 30);
    connect(boutonAnnuler, &QPushButton::clicked, this, &SettingArea::onBoutonAnnulerClicked);

}

SettingArea::~SettingArea()
{
    delete ui;
}

void SettingArea::onBoutonOuvrirClicked()
{
    //QString cheminInitial = "C:/Users/yasmi/OneDrive/Images";
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Sélectionnez un fichier", cheminInitial);

}

void SettingArea::onBoutonEnregistrerClicked()
{
    // enregistre l'image dans l'emplacement initial
}

void SettingArea::onBoutonEnregistrerSousClicked(){
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Enregistrer sous", cheminInitial);
    //enregistrer l'image (a faire)
}

void SettingArea::onBoutonAnnulerClicked(){
    //reviens a l'image d'origine
}

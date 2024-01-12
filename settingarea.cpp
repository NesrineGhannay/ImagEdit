#include "settingarea.h"
#include "ui_settingarea.h"
#include <QStandardPaths>
//#include "editionarea.h"

SettingArea::SettingArea(QWidget *parent) : QWidget(parent), ui(new Ui::SettingArea)
{
    ui->setupUi(this);

    boutonOuvrir = new QPushButton("Ouvrir", this);
    boutonOuvrir->setIcon(QIcon("C:/Users/yasmi/Downloads/open.png"));
    boutonOuvrir->setGeometry(10, 10, 100, 30);
    connect(boutonOuvrir, &QPushButton::clicked, this, &SettingArea::onBoutonOuvrirClicked);

    boutonEnregistrer = new QPushButton("Enregistrer", this);
    boutonEnregistrer->setIcon(QIcon("C:/Users/yasmi/Downloads/save.png"));
    boutonEnregistrer->setGeometry(120, 10, 100, 30);
    connect(boutonEnregistrer, &QPushButton::clicked, this, &SettingArea::onBoutonEnregistrerClicked);

    boutonEnregistrerSous = new QPushButton("Enregistrer sous", this);
    boutonEnregistrerSous->setIcon(QIcon("C:/Users/yasmi/Downloads/saveAs.png"));
    boutonEnregistrerSous->setGeometry(230, 10, 110, 30);
    connect(boutonEnregistrerSous, &QPushButton::clicked, this, &SettingArea::onBoutonEnregistrerSousClicked);

    boutonAnnuler = new QPushButton("Annuler", this);
    boutonAnnuler->setIcon(QIcon("C:/Users/yasmi/Downloads/cancel.png"));
    boutonAnnuler->setGeometry(350, 10, 100, 30);
    connect(boutonAnnuler, &QPushButton::clicked, this, &SettingArea::onBoutonAnnulerClicked);

    boutonRevenirArriere = new QPushButton(this);
    boutonRevenirArriere->setIcon(QIcon("C:/Users/yasmi/Downloads/arriere.png"));
    boutonRevenirArriere->setGeometry(460, 10, 50, 30);
    connect(boutonRevenirArriere, &QPushButton::clicked, this, &SettingArea::onBoutonRevenirArriereClicked);

    boutonRevenirAvant = new QPushButton(this);
    boutonRevenirAvant->setIcon(QIcon("C:/Users/yasmi/Downloads/avant.png"));
    boutonRevenirAvant->setGeometry(520, 10, 50, 30);
    connect(boutonRevenirAvant, &QPushButton::clicked, this, &SettingArea::onBoutonRevenirAvantClicked);

    boutonPlus = new QPushButton(this);
    boutonPlus->setIcon(QIcon("C:/Users/yasmi/Downloads/plus.png"));
    boutonPlus->setGeometry(580, 10, 50, 30);
    connect(boutonPlus, &QPushButton::clicked, this, &SettingArea::onBoutonPlusClicked);

    boutonMoins = new QPushButton(this);
    boutonMoins->setIcon(QIcon("C:/Users/yasmi/Downloads/moins.png"));
    boutonMoins->setGeometry(640, 10, 50, 30);
    connect(boutonMoins, &QPushButton::clicked, this, &SettingArea::onBoutonMoinsClicked);

    boutonSupprimer = new QPushButton("Supprimer",this);
    boutonSupprimer->setIcon(QIcon("C:/Users/yasmi/Downloads/suppr.png"));
    boutonSupprimer->setGeometry(700, 10, 100, 30);
    connect(boutonSupprimer, &QPushButton::clicked, this, &SettingArea::onBoutonSupprimerClicked);

    logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap("C:/Users/yasmi/Downloads/logo3.png"));
    logoLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
    //logoLabel->setGeometry(width() - 200, -5, 90, 50);
    logoLabel->setGeometry(990, -5, 210, 210);

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

void SettingArea::onBoutonRevenirArriereClicked(){

}

void SettingArea::onBoutonRevenirAvantClicked(){

}

void SettingArea::onBoutonPlusClicked(){

}

void SettingArea::onBoutonMoinsClicked(){

}

void SettingArea::onBoutonSupprimerClicked(){

}

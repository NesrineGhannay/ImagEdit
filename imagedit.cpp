#include "imagedit.h"
#include "ui_imagedit.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QPixmap>
#include <QIcon>
#include <QGridLayout>
#include <QShortcut>
#include <QKeySequence>

ImagEdit::ImagEdit(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImagEdit)
{
    ui->setupUi(this);
    path = new QString();
    pix = new QPixmap(*path);
    QList<QPushButton*> tousLesBoutons = findChildren<QPushButton*>();
    for (QPushButton* bouton : tousLesBoutons) {
        bouton->setStyleSheet("QPushButton:pressed {border: 2px solid #00f;}"
                              "QPushButton { border: 1px solid #000;}");
    }

    raccourciEnregistrer = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);
    raccourciOuvrir = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this);

    connect(raccourciEnregistrer, &QShortcut::activated, this, &ImagEdit::on_save_clicked);
    connect(raccourciOuvrir, &QShortcut::activated, this, &ImagEdit::on_open_clicked);
}

ImagEdit::~ImagEdit()
{
    delete ui;
    delete pix;
    delete path;
}



void ImagEdit::on_open_clicked()
{
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList cheminsFichiers = QFileDialog::getOpenFileNames(this, "Sélectionnez des fichiers", cheminInitial);
    selectedImagePaths.append(cheminsFichiers);
    QGridLayout* existingLayout = dynamic_cast<QGridLayout*>(ui->library->layout());

    if (!existingLayout) {
        existingLayout = new QGridLayout;
        ui->library->setLayout(existingLayout);
    }

    QLayoutItem *child;
    while ((child = existingLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    const int gridSize = 100;
    for (int i = 0; i < selectedImagePaths.size(); ++i) {
        QPixmap pix(selectedImagePaths[i]);
        pix = pix.scaled(gridSize, gridSize, Qt::KeepAspectRatio);

        QPushButton *button = new QPushButton;
        button->setIcon(QIcon(pix));
        button->setIconSize(pix.size());
        existingLayout->addWidget(button, i / 3, i % 3);

        connect(button, &QPushButton::clicked, [=]() { displayOnEdition(i); });

    }

}

void ImagEdit::displayOnEdition(int index)
{
    if (index >= 0 && index < selectedImagePaths.size()) {
        QString selectedImagePath = selectedImagePaths.at(index);
        QPixmap pix(selectedImagePath);
        pix = pix.scaled(600, 300, Qt::KeepAspectRatio);
        ui->imageLabel->setPixmap(pix);
    }
}



void ImagEdit::on_save_under_clicked()
{
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", cheminInitial, "Images (*.png *.jpg *.bmp);;Tous les fichiers (*.*)");
    if (!cheminFichier.isEmpty()) {
        QPixmap pixmap = ui->imageLabel->pixmap();
        if (!pixmap.save(cheminFichier)) {
            //erreur
        }
    }
}


void ImagEdit::on_save_clicked()
{

    if (!ui->imageLabel->pixmap()) {
        QMessageBox::warning(this, "Aucune image", "Aucune image à enregistrer.");
        return;
    }
    if (currentIndex < 0 || currentIndex >= selectedImagePaths.size()) {
        QMessageBox::warning(this, "Erreur", "L'index de l'image actuelle n'est pas valide.");
        return;
    }
    QString cheminFichier = selectedImagePaths[currentIndex];
    QPixmap pixmap = ui->imageLabel->pixmap();
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Erreur", "La pixmap de l'image actuelle est invalide.");
        return;
    }
    if (!pixmap.save(cheminFichier)) {
        QMessageBox::warning(this, "Erreur d'enregistrement", "L'enregistrement a échoué.");
    } else {
        qDebug() << "Enregistrement réussi !";
        QMessageBox::warning(this, "Sauvegarde réussi", "Image enregistrée avec succès.");
    }

}


void ImagEdit::on_filter_clicked()
{
    FilterArea *filterarea = new FilterArea();
    //connect(filterarea, filterarea->appliquerFiltreNoirEtBlanc(pix->toImage()), this, ui->imageLabel);
    //filterarea->setImage(ui->imageLabel->pixmap().toImage());
    //ui->imageLabel->clear();
    filterarea->setLabel(ui->imageLabel);
    filterarea->show();
}



void ImagEdit::on_rogner_clicked()
{
    RognerArea *rogner = new RognerArea();
    rogner->show();
}







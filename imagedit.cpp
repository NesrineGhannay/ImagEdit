#include "imagedit.h"
#include "ui_imagedit.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDebug>

ImagEdit::ImagEdit(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImagEdit)
{
    ui->setupUi(this);
    path = new QString();
    pix = new QPixmap(*path);
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
    for (const QString& cheminFichier : cheminsFichiers) {
        QPushButton *button = new QPushButton(cheminFichier, this);
        connect(button, SIGNAL(clicked()), this, SLOT(displayOnEdition()));
        QListWidgetItem *item = new QListWidgetItem;
        ui->library->addItem(item);
        ui->library->setItemWidget(item, button);
    }
}
void ImagEdit::displayOnEdition()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        int index = ui->library->indexAt(clickedButton->pos()).row();
        if (index >= 0 && index < selectedImagePaths.size()) {
            QString selectedImagePath = selectedImagePaths.at(index);
            // Utilisez le chemin du fichier pour afficher l'image
            QPixmap pix(selectedImagePath);
            pix = pix.scaled(600, 300, Qt::KeepAspectRatio);
            ui->imageLabel->setPixmap(pix);
        }
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
    //Vérifie s'il y a une image affichée
    if (!ui->imageLabel->pixmap()) {
        return;
    }

    //le chemin d'origine de l'image
    QString cheminFichier = selectedImagePaths.value(ui->library->currentRow());

    // Vérifie si le chemin du fichier d'origine est valide
    if (cheminFichier.isEmpty()) {
        return;
    }

    QPixmap pixmap = ui->imageLabel->pixmap();
    if (!pixmap.save(cheminFichier)) {
        //erreur
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







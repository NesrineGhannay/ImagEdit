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
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Sélectionnez un fichier", cheminInitial);
    QFileInfo fileInfo(cheminFichier);
    QString nomFichier = fileInfo.fileName();
    QPushButton *button = new QPushButton(nomFichier, this);

    connect(button, SIGNAL(clicked()), this, SLOT(displayOnEdition()));
    *path = cheminFichier;
    QListWidgetItem *item = new QListWidgetItem;

    ui->library->addItem(item);
    ui->library->setItemWidget(item, button);
}

void ImagEdit::displayOnEdition()
{
    QPixmap pix(*path);
    pix = pix.scaled(381, 271, Qt::KeepAspectRatio);
    ui->imageLabel->setPixmap(pix);

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







#include "rognerarea.h"
#include "ui_rognerarea.h"

RognerArea::RognerArea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RognerArea)
{
    ui->setupUi(this);

}

QImage RognerArea::getImage() const
{
    if (const QPixmap &pixmap = ui->image->pixmap(); !pixmap.isNull()) {
        QImage currentImage = pixmap.toImage();
        return currentImage;
    }
    return QImage();
}



void RognerArea::setImage(const QImage &image)
{
    ui->image->setPixmap(QPixmap::fromImage(image));
}

void RognerArea::rognageImage()
{
    QImage image = getImage();

    if (!imageActuelle.isNull()) {

        //ici il faudra récuperer la taille de la widget et l'appliquer avec cette fonction
        QRect cropRect(0, 0, 100, 100);

        // on créé une nouvelle image pour stocker la partie rogner (seulement si on clique sur le boutton ok)
        QImage croppedImage = image.copy(cropRect);

        //on affiche ensuite l'image dans la partie edition
        ui->image->setPixmap(QPixmap::fromImage(croppedImage));
    }
    else {
        qDebug() << "Erreur : Aucune image actuelle à traiter.";
    }
}

void RognerArea::Rogner_clickedMouse()
{
    // Appeler la fonction de rognage lorsque l'on lache la souris et qu'on appuie sur ok ?!
    rognageImage();
}


RognerArea::~RognerArea()
{
    delete ui;
}


#include "imagedit.h"
#include "ui_imagedit.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>



ImagEdit::ImagEdit(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImagEdit)
{
    ui->setupUi(this);
    path = new QString();
    fileName = new QString();
    pix = new QPixmap();
    rect = new QRect();

    boutonFiltre = findChild<QPushButton*>("filter");

    widgetFilter = new FilterArea(this);
    setupFilterButtonConnection();
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
    *fileName = fileInfo.fileName();
    QPushButton *button = new QPushButton(*fileName, this);

    connect(button, SIGNAL(clicked()), this, SLOT(displayOnEdition()));
    *path = cheminFichier;
    QListWidgetItem *item = new QListWidgetItem;

    ui->library->addItem(item);
    ui->library->setItemWidget(item, button);
}

void ImagEdit::setupFilterButtonConnection()
{
    widgetFilter->setVisible(false);
    int x = 750;
    int y = 100;
    widgetFilter->move(x, y);

    if (boutonFiltre && widgetFilter) {
        connect(boutonFiltre, SIGNAL(clicked()), widgetFilter, SLOT(on_filter_clicked()));
    }

    //connect(boutonFiltre, SIGNAL(clicked()), widgetFilter, SLOT(on_filter_clicked()));
}

void ImagEdit::on_filter_clicked()
{
    qDebug() << "Bouton filtre cliqué !";

    // Créez une animation pour animer la propriété "geometry" de widgetFilter
    QPropertyAnimation *animation = new QPropertyAnimation(widgetFilter, "geometry", this);

    // Définissez la durée de l'animation (en millisecondes)
    animation->setDuration(500);  // Réglez cette valeur selon vos préférences

    // Définissez les valeurs de début et de fin pour l'animation
    QRect startRect = widgetFilter->geometry();
    QRect endRect = QRect(750, 100, widgetFilter->width(), widgetFilter->height());

    animation->setStartValue(startRect);
    animation->setEndValue(endRect);

    // Démarrez l'animation
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    // Changez la visibilité de widgetFilter en fonction de l'animation
    widgetFilter->setVisible(!widgetFilter->isVisible());

    qDebug() << "Nouvel état de visibilité de widgetFilter : " << widgetFilter->isVisible();
}


/*void ImagEdit::on_filter_clicked()
{
    //filterarea = new FilterArea();
    //filterarea->setLabel(actualCropping);

    qDebug() << "Bouton cliqué !";
    widgetFilter->setVisible(!widgetFilter->isVisible());
    qDebug() << "Nouvel état de visibilité de widgetFilter : " << widgetFilter->isVisible();
    qDebug() << "Interface utilisateur : " << boutonFiltre->isVisible();
}*/

void ImagEdit::on_rogner_clicked()
{
    if(!actualCropping->getIsCropping()) {
        actualCropping->drawRectCropping(pix);
    }
    else {
        actualCropping->deleteRectCropping();
        *pix = actualCropping->getPixmap();
        update();
    }
}
void ImagEdit::displayOnEdition()
{

    pix = new QPixmap(*path);
    *pix = pix->scaled(381, 271, Qt::KeepAspectRatio);

    actualCropping = new Cropping();
    actualCropping->setPixmap(*pix);
    actualCropping->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tabWidget->addTab(actualCropping, *fileName);

}

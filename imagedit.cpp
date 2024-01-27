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
    fileName = new QString();
    pix = new QPixmap();
    rect = new QRect();

    QVBoxLayout *layout = new QVBoxLayout(this);
    //QPushButton *filter = new QPushButton("Afficher le contenu de Widget 2", this);
    //layout->addWidget(filter);

    QPushButton *boutonFiltre = findChild<QPushButton*>("filter");
    //layout->addWidget(boutonFiltre);

    qDebug() << "Before creating widgetFilter";
    widgetFilter = new FilterArea(this);
    qDebug() << "After creating widgetFilter";
    qDebug() << "Initial Visibility: " << widgetFilter->isVisible();
    layout->addWidget(widgetFilter);
    widgetFilter->setVisible(false);

    int x = 740; // position x
    int y = 100; // position y
    widgetFilter->move(x, y);

    /*
    if (boutonFiltre) {
        layout->addWidget(boutonFiltre);
        connect(boutonFiltre, SIGNAL(clicked()), this, SLOT(on_filter_clicked()));
    }*/

    connect(boutonFiltre, SIGNAL(clicked()), this, SLOT(on_filter_clicked()));

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


void ImagEdit::on_filter_clicked()
{
    //filterarea = new FilterArea();
    //filterarea->setLabel(actualCropping);
    //filterarea->show();
    qDebug() << "Bouton cliqué !";
    widgetFilter->setVisible(!widgetFilter->isVisible());

}

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

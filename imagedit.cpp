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
    filterarea = new FilterArea();

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
    if(!filterarea->getIsFilter()) {
        filterarea->setLabel(actualCropping);
        filterarea->show();
        filterarea->setIsFilter(true);
    } else {
        filterarea->close();
        filterarea->setIsFilter(false);
    }

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

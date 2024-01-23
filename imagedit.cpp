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
    pix = new QPixmap();

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
    pix = new QPixmap(*path);
    *pix = pix->scaled(381, 271, Qt::KeepAspectRatio);

    //QLabel *label1 = new QLabel(this);
    //label1->setPixmap(*pix);

    ui->imageLabel->setPixmap(*pix);

}


void ImagEdit::on_filter_clicked()
{
    filterarea = new FilterArea();
    filterarea->setLabel(ui->imageLabel);
    filterarea->show();
}



void ImagEdit::on_rogner_clicked()
{

    QPainter painter(pix);
    painter.setPen(QPen(Qt::blue, 2));
    QColor grayWithAlpha = QColor(128, 128, 128, 128);  // Adjust the alpha value as needed
    painter.setBrush(QBrush(grayWithAlpha));
    cout << pix-> height() << endl;
    cout << pix-> width() << endl;
    painter.drawRect(0, 0, pix->width(), pix->height());

    ui->imageLabel->setPixmap(*pix);

}





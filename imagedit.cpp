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
}

ImagEdit::~ImagEdit()
{
    delete ui;
}

void ImagEdit::on_open_clicked()
{
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Sélectionnez un fichier", cheminInitial);
    QPushButton *button = new QPushButton(cheminFichier, this);
    connect(button, SIGNAL(clicked()), this, SLOT(displayOnEdition()));

    QListWidgetItem *item = new QListWidgetItem;

    ui->library->addItem(item);
    ui->library->setItemWidget(item, button);
}

void ImagEdit::displayOnEdition()
{
    QString myString = QStringLiteral("Hello, World!");
    ui->edition->addItem(myString);

}

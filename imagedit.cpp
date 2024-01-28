#include "imagedit.h"
#include "ui_imagedit.h"


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



/*void ImagEdit::on_open_clicked()
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
}*/


void ImagEdit::on_open_clicked()
{
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Sélectionnez un fichier", cheminInitial);
    QFileInfo fileInfo(cheminFichier);
    *fileName = fileInfo.fileName();
    QPushButton *button = new QPushButton(*fileName, this);

    QGridLayout* existingLayout = dynamic_cast<QGridLayout*>(ui->library->layout()); // add after
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
        connect(button, SIGNAL(clicked()), this, SLOT(displayOnEdition()));

        existingLayout->addWidget(button, i / 3, i % 3);

        *path = cheminFichier;
        QListWidgetItem *item = new QListWidgetItem;
        ui->library->addItem(item);
        ui->library->setItemWidget(item, button);


        //connect(button, &QPushButton::clicked, [=]() { displayOnEdition(i); });

    }

}

/*void ImagEdit::displayOnEdition(int index)
{
    if (index >= 0 && index < selectedImagePaths.size()) {
        QString selectedImagePath = selectedImagePaths.at(index);
        QPixmap pix(selectedImagePath);
        pix = pix.scaled(600, 300, Qt::KeepAspectRatio);
        ui->imageLabel->setPixmap(pix);
    }
}*/



void ImagEdit::on_save_under_clicked()
{
    /*
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", cheminInitial, "Images (*.png *.jpg *.bmp);;Tous les fichiers (*.*)");
    if (!cheminFichier.isEmpty()) {
        QPixmap pixmap = ui->imageLabel->pixmap();
        if (!pixmap.save(cheminFichier)) {
            //erreur
        }
    }*/
}


void ImagEdit::on_save_clicked()
{
/*
    if (!ui->cropping->pixmap()) {
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
    */
}

void ImagEdit::setupFilterButtonConnection()
{
    widgetFilter->setVisible(false);
    int x = 750;
    int y = 100;
    widgetFilter->move(x, y);

    connect(boutonFiltre, SIGNAL(clicked()), widgetFilter, SLOT(on_filter_clicked()));
}

void ImagEdit::on_filter_clicked()
{
    widgetFilter->setLabel(actualCropping);
    widgetFilter->show();
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

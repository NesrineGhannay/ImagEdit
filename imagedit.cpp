#include "imagedit.h"
#include "ui_imagedit.h"


ImagEdit::ImagEdit(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImagEdit)
{
    ui->setupUi(this);
    path = new QString();
    pix = new QPixmap(*path);
    QList<QPushButton*> tousLesBoutons = findChildren<QPushButton*>();

    raccourciEnregistrer = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);
    raccourciOuvrir = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this);
    //croppingButtons = new QList<QPushButton*>();
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

void ImagEdit::on_open_clicked()
{
    ui->importImage->close();
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Sélectionnez un fichier", cheminInitial);
    QFileInfo fileInfo(cheminFichier);
    *fileName = fileInfo.fileName();
    *path = cheminFichier;
    originalPaths.append(*path);
    pix = new QPixmap(*path);
    *pix = pix->scaled(gridSize, gridSize, Qt::KeepAspectRatio);

    QPushButton *button = new QPushButton();
    croppingButtons.append(button);

    button->setIcon(QIcon(*pix));
    button->setIconSize(pix->size());
    button->setStyleSheet("QPushButton:pressed {border: 1px solid #00f;} ""QPushButton { border: 1px solid ;}");
    button->setFixedSize(40, 40);
    ui->gridLayout->addWidget(button);

    updateLibraryVisualisation();
}

void ImagEdit::updateLibraryVisualisation() {
    int c = 0;
    qDebug() << croppingButtons.size();
    for(int i = 0; i < ui->gridLayout->count(); i++) {
        if(i%3 == 0 && i != 0) c++;
        ui->gridLayout->addWidget(croppingButtons[i], c, i%3);
        connect(croppingButtons[i], SIGNAL(clicked()), this, SLOT(displayOnEdition()));
    }
    update();
}




void ImagEdit::setCurrentImage()
{
    actualCropping = qobject_cast<Cropping*>(ui->tabWidget->currentWidget());
    widgetFilter->setLabel(actualCropping);
    update();
}

void ImagEdit::on_save_under_clicked()
{
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", cheminInitial, "Images (*.png *.jpg *.bmp);;Tous les fichiers (*.*)");
    if (!cheminFichier.isEmpty()) {

        QPixmap pixmap = actualCropping->getPixmap();
        if (!pixmap.save(cheminFichier)) {
            //erreur
        }
    }
}

void ImagEdit::on_save_clicked()
{

    if (!actualCropping->pixmap()) {
        QMessageBox::warning(this, "Aucune image", "Aucune image à enregistrer.");
        return;
    }
    /* (currentIndex < 0 || currentIndex >= selectedImagePaths.size()) {
        QMessageBox::warning(this, "Erreur", "L'index de l'image actuelle n'est pas valide.");
        return;
    }*/
    QString cheminFichier = originalPaths[currentIndex];
    QPixmap pixmap = actualCropping->pixmap();
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

void ImagEdit::setupFilterButtonConnection()
{
    widgetFilter->setVisible(false);
    int x = 750;
    int y = 100;
    widgetFilter->move(x, y);


}

void ImagEdit::on_filter_clicked()
{
    if(ui->tabWidget->count() == 0) {
        QMessageBox::warning(this, "No image found", "No image selected");
    } else {
        widgetFilter->setIsFilter(true);
        widgetFilter->setLabel(actualCropping);
        widgetFilter->show();
    }

}

void ImagEdit::on_rogner_clicked() {
    if(ui->tabWidget->count() == 0) {
        QMessageBox::warning(this, "No image found", "No image selected");
    } else {
        if(!actualCropping->getIsCropping()) {
            actualCropping->drawRectCropping(pix);
        }
        else {
            actualCropping->deleteRectCropping();
            *pix = actualCropping->getPixmap();
            update();
        }
    }

}

void ImagEdit::displayOnEdition()
{

    pix = new QPixmap(*path);
    *pix = pix->scaled(381, 271, Qt::KeepAspectRatio);

    actualCropping = new Cropping();
    actualCropping->setPixmap(*pix);
    actualCropping->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentImage()));


    ui->tabWidget->addTab(actualCropping, *fileName);

}

void ImagEdit::on_importImage_clicked()
{

    ui->importImage->close();
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Sélectionnez un fichier", cheminInitial);
    QFileInfo fileInfo(cheminFichier);
    *fileName = fileInfo.fileName();
    *path = cheminFichier;
    originalPaths.append(*path);
    QPushButton *button = new QPushButton();

    croppingButtons.append(button);




    pix = new QPixmap(*path);
    *pix = pix->scaled(gridSize, gridSize, Qt::KeepAspectRatio);
    button->setIcon(QIcon(*pix));
    button->setIconSize(pix->size());
    *path = cheminFichier;
    button->setStyleSheet("QPushButton:pressed {border: 2px solid #00f;} ""QPushButton { border: 1px solid ;}");
    button->setFixedSize(40, 40);
    ui->gridLayout->addWidget(button);
    updateLibraryVisualisation();
}


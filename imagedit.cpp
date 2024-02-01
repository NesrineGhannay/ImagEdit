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
    currentIndex = 0;
    //QList<Cropping*> croppingList;
    //QList<QPushButton*> croppingButtons;


    boutonFiltre = findChild<QPushButton*>("filter");
    widgetFilter = new FilterArea(this);
    setupFilterButtonConnection();
}



void ImagEdit::on_open_clicked()
{
    /*
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString cheminFichier = QFileDialog::getOpenFileName(this, "Sélectionnez un fichier", cheminInitial);
    QFileInfo fileInfo(cheminFichier);
    *fileName = fileInfo.fileName();
    *path = cheminFichier;
    originalPaths.append(*path);
    QPushButton *button = new QPushButton();

    croppingButtons.append(button);

    const int gridSize = 30;

    pix = new QPixmap(*path);
    *pix = pix->scaled(gridSize, gridSize, Qt::KeepAspectRatio);
    button->setIcon(QIcon(*pix));
    button->setIconSize(pix->size());
    *path = cheminFichier;
    //button->setStyleSheet("QPushButton:pressed {border: 2px solid #00f;} ""QPushButton { border: 1px solid ;}");
    button->setFixedSize(40, 40);
    ui->gridLayout->addWidget(button);
    updateLibraryVisualisation();
    */


    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList cheminsFichiers = QFileDialog::getOpenFileNames(this, "Sélectionnez des fichiers", cheminInitial);

    for (const QString &filePath : cheminsFichiers) {
        originalPaths.append(filePath);
        QPixmap *pix = new QPixmap(filePath);
        *pix = pix->scaled(381, 271, Qt::KeepAspectRatio);

        QPushButton *button = new QPushButton();
        button->setIcon(QIcon(*pix));
        button->setIconSize(pix->size());
        button->setFixedSize(40, 40);
        croppingButtons.append(button);
        ui->gridLayout->addWidget(button);



        Cropping *cropping = new Cropping();
        cropping->setPixmap(*pix);
        cropping->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        croppingList.append(cropping);

        connect(button, &QPushButton::clicked, this, [=]() {
            int index = croppingButtons.indexOf(button);
            if (index != -1 && index < croppingList.size()) {
                actualCropping = croppingList[index];
                displayOnEdition(index);
            }
        });
        ui->tabWidget->addTab(cropping, QFileInfo(filePath).fileName());

        updateLibraryVisualisation();
    }

}

void ImagEdit::updateLibraryVisualisation() {
    /*
    int c = 0;
    for(int i = 0; i < ui->gridLayout->count(); i++) {
        if(i%3 == 0 && i != 0) c++;
        ui->gridLayout->addWidget(croppingButtons[i], c, i%3);
        connect(croppingButtons[i], SIGNAL(clicked()), this, SLOT(displayOnEdition()));
    }
    update();
    */
    int c = 0;
    for(int i = 0; i < ui->gridLayout->count(); i++) {
        if(i % 3 == 0 && i != 0) c++;

        QPushButton *button = croppingButtons[i];
        int index = i;
        connect(button, &QPushButton::clicked, this, [=]() {
            displayOnEdition(index);
        });

        ui->gridLayout->addWidget(button, c, i % 3);
    }
    update();
}

void ImagEdit::displayOnEdition(int index)
{
    /*
        pix = new QPixmap(*path);
        *pix = pix->scaled(381, 271, Qt::KeepAspectRatio);
        actualCropping = new Cropping();
        actualCropping->setPixmap(*pix);
        actualCropping->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentImage()));
        ui->tabWidget->addTab(actualCropping, *fileName);
    */

    /*
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentImage()));
    if (ui->tabWidget->indexOf(actualCropping) == -1) {
        ui->tabWidget->addTab(actualCropping, QFileInfo(*fileName).fileName());
    }

    int currentTabIndex = ui->tabWidget->indexOf(actualCropping);
    ui->tabWidget->setCurrentIndex(currentTabIndex);
    currentIndex++;
    */
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentImage()));
    if (index >= 0 && index < croppingList.size()) {
        actualCropping = croppingList[index];
    } else {
        qDebug() << "Index invalide : " << index;
        return;
    }

    if (ui->tabWidget->indexOf(actualCropping) == -1) {
        ui->tabWidget->addTab(actualCropping, QFileInfo(*fileName).fileName());
    }

    int currentTabIndex = ui->tabWidget->indexOf(actualCropping);
    ui->tabWidget->setCurrentIndex(currentTabIndex);
    currentIndex = index;  // Mise à jour de l'index

}


void ImagEdit::setCurrentImage()
{
    actualCropping = qobject_cast<Cropping*>(ui->tabWidget->currentWidget());
    widgetFilter->setLabel(actualCropping);
    currentIndex = ui->tabWidget->currentIndex();
    update();
}

void ImagEdit::on_save_under_clicked()
{
    if (currentIndex < 0 || currentIndex >= croppingList.size()) {
        QMessageBox::warning(this, "Erreur", "L'index de l'image actuelle n'est pas valide.");
        return;
    }

    Cropping *currentCropping = croppingList.at(currentIndex);

    QString cheminFichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", "", "Images (*.png *.jpg *.bmp);;Tous les fichiers (*.*)");
    if (!cheminFichier.isEmpty()) {
        QPixmap pixmap = currentCropping->getPixmap();

        if (!pixmap.save(cheminFichier)) {
            QMessageBox::warning(this, "Erreur d'enregistrement", "L'enregistrement a échoué.");
        } else {
            qDebug() << "Enregistrement réussi !";
            QMessageBox::information(this, "Sauvegarde réussie", "Image enregistrée avec succès.");
        }
    }
}

void ImagEdit::on_save_clicked()
{
    /*
    if (croppingList.isEmpty() || currentIndex < 0 || currentIndex >= croppingList.size()) {
        QMessageBox::warning(this, "Aucune image", "Aucune image sélectionnée.");
        return;
    }


    // (currentIndex < 0 || currentIndex >= selectedImagePaths.size()) {
    //    QMessageBox::warning(this, "Erreur", "L'index de l'image actuelle n'est pas valide.");
    //    return;
    //}
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
    */

    if (currentIndex < 0 || currentIndex >= croppingList.size()) {
        QMessageBox::warning(this, "Erreur", "L'index de l'image actuelle n'est pas valide.");
        return;
    }

    Cropping *currentCropping = croppingList.at(currentIndex);
    if (!currentCropping) {
        qDebug() << "L'objet Cropping pour l'index actuel est invalide.";
        return;
    }
    if (currentIndex >= 0 && currentIndex < originalPaths.size()) {
        QString cheminFichier = originalPaths[currentIndex];
        QPixmap pixmap = currentCropping->getPixmap();
        if (pixmap.isNull()) {
            QMessageBox::warning(this, "Erreur", "La pixmap de l'image actuelle est invalide.");
            return;
        }

        // Enregistrer l'image
        if (!pixmap.save(cheminFichier)) {
            QMessageBox::warning(this, "Erreur d'enregistrement", "L'enregistrement a échoué.");
        } else {
            qDebug() << "Enregistrement réussi !";
            QMessageBox::information(this, "Sauvegarde réussie", "Image enregistrée avec succès.");
        }
    } else {
        qDebug() << "L'index actuel est hors de portée dans originalPaths.";
        QMessageBox::warning(this, "Erreur", "L'index de l'image actuelle est hors de portée.");
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
    widgetFilter->setLabel(actualCropping);
    widgetFilter->show();
}

void ImagEdit::on_rogner_clicked() {
    if(!actualCropping->getIsCropping()) {
        actualCropping->drawRectCropping(pix);
    }
    else {
        actualCropping->deleteRectCropping();
        *pix = actualCropping->getPixmap();
        update();
    }
}


ImagEdit::~ImagEdit()
{
    delete ui;
    delete pix;
    delete path;
}

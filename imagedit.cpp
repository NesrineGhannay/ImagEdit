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

    connect(ui->zoom, &QPushButton::clicked, this, &ImagEdit::on_zoom_clicked);
    connect(ui->dezoom, &QPushButton::clicked, this, &ImagEdit::on_zoom_clicked);

    connect(ui->cancel, &QPushButton::clicked, [=]() {
        on_cancelButton_clicked(currentIndex);
    });

    connect(ui->cancel_2, &QPushButton::clicked, this, &ImagEdit::onCancel2ButtonClicked);

    fileName = new QString();
    pix = new QPixmap();
    rect = new QRect();
    currentIndex = 0;

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

        //bouton image ds library
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
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentImage()));
    if (index >= 0 && index < croppingList.size()) {
        actualCropping = croppingList[index];
    } else {
        return;
    }

    if (ui->tabWidget->indexOf(actualCropping) == -1) {
        ui->tabWidget->addTab(actualCropping, QFileInfo(*fileName).fileName());
    }

    int currentTabIndex = ui->tabWidget->indexOf(actualCropping);
    ui->tabWidget->setCurrentIndex(currentTabIndex);
    currentIndex = index;  // Mise à jour de l'index
    */

    /*
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentImage()));

       if (index >= 0 && index < croppingList.size())
       {
           QPixmap currentState = actualCropping->getPixmap();
           undoHistory.append(currentState);
           actualCropping = croppingList[index];

           if (actualCropping->getPixmap().isNull())
           {
               qDebug() << "La pixmap de l'image actuelle est invalide.";
               return;
           }
       }
       else
       {
           qDebug() << "Index invalide : " << index;
           return;
       }

       if (ui->tabWidget->indexOf(actualCropping) == -1)
       {
           ui->tabWidget->addTab(actualCropping, QFileInfo(*fileName).fileName());
       }

       int currentTabIndex = ui->tabWidget->indexOf(actualCropping);
       ui->tabWidget->setCurrentIndex(currentTabIndex);
       currentIndex = index;
       */
    disconnect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentImage()));

    if (index >= 0 && index < croppingList.size())
    {
        actualCropping = croppingList[index];
        if (actualCropping->getPixmap().isNull())
        {
            qDebug() << "La pixmap de l'image actuelle est invalide.";
            return;
        }
    }
    else
    {
        qDebug() << "Index invalide : " << index;
        return;
    }

    if (ui->tabWidget->indexOf(actualCropping) == -1)
    {
        ui->tabWidget->addTab(actualCropping, QFileInfo(*fileName).fileName());
    }

    int currentTabIndex = ui->tabWidget->indexOf(actualCropping);
    ui->tabWidget->setCurrentIndex(currentTabIndex);
    currentIndex = index;

    // Reconnectez le signal currentChanged après avoir terminé le traitement
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(setCurrentImage()));

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

void ImagEdit::updateIndicesAfterRemoval(int removedIndex)
{
    if (currentIndex == removedIndex) {
        //image actuelle supprimée
        currentIndex = -1;
    } else if (currentIndex > removedIndex) {
        // image actuelle  après l'image supprimée
        currentIndex--;
    }
}


void ImagEdit::resetInterface()
{
    currentIndex = -1;
    actualCropping = nullptr;
    ui->tabWidget->clear();
    croppingList.clear();
    croppingButtons.clear();
    originalPaths.clear();
    ui->gridLayout->removeItem(ui->gridLayout->itemAt(0));
}

void ImagEdit::on_cancelButton_clicked(int index)
{
    if (index >= 0 && index < croppingList.size()) {
        ui->tabWidget->removeTab(index);
        Cropping *cropping = croppingList.takeAt(index);
        QPushButton *button = croppingButtons.takeAt(index);
        delete cropping;
        delete button;
        updateIndicesAfterRemoval(index);
        if (croppingList.isEmpty()) {
            resetInterface();
        } else {
            int newCurrentIndex = qBound(0, currentIndex, croppingList.size() - 1);
            displayOnEdition(newCurrentIndex);
        }
    }
}

void ImagEdit::on_zoom_clicked()
{
    qreal zoomFactor = 1.15;
    if (currentIndex >= 0 && currentIndex < croppingList.size())
    {
        actualCropping = croppingList[currentIndex];
        actualCropping->updateZoom(zoomFactor);
    }
}
void ImagEdit::on_dezoom_clicked()
{
    qreal zoomFactor = 0.75;
    if (currentIndex >= 0 && currentIndex < croppingList.size())
    {
        actualCropping = croppingList[currentIndex];
        actualCropping->updateZoom(zoomFactor);
    }
}

void ImagEdit::onCancel2ButtonClicked()
{
    if (currentIndex >= 0 && currentIndex < originalPaths.size())
    {

        QPixmap originalPixmap(originalPaths[currentIndex]);
        actualCropping->setPixmap(originalPixmap);
        update();
    }
    else
    {
        qDebug() << "L'index actuel est invalide pour annuler.";
    }
}

ImagEdit::~ImagEdit()
{
    delete ui;
    delete pix;
    delete path;
}

#include "imagedit.h"
#include "ui_imagedit.h"


ImagEdit::ImagEdit(QWidget *parent) : QMainWindow(parent), ui(new Ui::ImagEdit)
{
    ui->setupUi(this);
    ui->tabWidget->setStyleSheet("background-color:black;");
    path = new QString();
    pix = new QPixmap(*path);
    QList<QPushButton*> tousLesBoutons = findChildren<QPushButton*>();
    confirmCropping = new QPushButton("Rogner", this);
    confirmCropping->hide();
    cancelCropping = new QPushButton("Annuler", this);
    cancelCropping->hide();

    boutonResize = findChild<QPushButton*>("resize");
    resize = new Resize(this);
    setupResizeButtonConnection();
    raccourciEnregistrer = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);
    raccourciOuvrir = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_O), this);
    racourciEchapCropping = new QShortcut(QKeySequence(Qt::Key_Escape), this);

    connect(raccourciEnregistrer, &QShortcut::activated, this, &ImagEdit::on_save_clicked);
    connect(raccourciOuvrir, &QShortcut::activated, this, &ImagEdit::on_open_clicked);

    connect(ui->zoom, &QPushButton::clicked, this, &ImagEdit::on_zoom_clicked);
    connect(ui->dezoom, &QPushButton::clicked, this, &ImagEdit::on_zoom_clicked);

    connect(ui->cancel, &QPushButton::clicked, [=]() {
        on_cancelButton_clicked(currentIndex);
    });

    //connect(ui->cancel_2, &QPushButton::clicked, this, &ImagEdit::onCancel2ButtonClicked);

    fileName = new QString();
    pix = new QPixmap();
    rect = new QRect();
    currentIndex = 0;

    boutonFiltre = findChild<QPushButton*>("filter");
    widgetFilter = new FilterArea(this);
    setupFilterButtonConnection();

    boutonResize = findChild<QPushButton*>("resize");
    resize = new Resize(this);
    setupResizeButtonConnection();
    resize->hide();

}



void ImagEdit::setupResizeButtonConnection()
{
    resize->setVisible(false);
    int x = 770;
    int y = 130;
    resize->move(x, y);


}

void ImagEdit::on_open_clicked()
{
    /*
    QString cheminInitial = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

    QString selfilter = tr("JPEG (*.jpg *.jpeg)");
    QString cheminFichier = QFileDialog::getOpenFileName(
        this,
        "Sélectionnez un fichier",
        cheminInitial,
        tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" ),
        &selfilter
        );

    QFileInfo fileInfo(cheminFichier);
    *fileName = fileInfo.fileName();

    if(!fileName->isEmpty()) {
        ui->importImage->close();
        *path = cheminFichier;
        originalPaths.append(*path);
        pix = new QPixmap(*path);
        *pix = pix->scaled(gridSize, gridSize, Qt::KeepAspectRatio);

        QPushButton *button = new QPushButton();
        croppingButtons.append(button);

        button->setIcon(QIcon(*pix));
        button->setIconSize(pix->size());
        button->setStyleSheet("QPushButton:pressed {border: 1px solid #00f;} ""QPushButton { border: 1px solid ;}");
        button->setFixedSize(50, 50);
        ui->gridLayout->addWidget(button);

        if(ui->gridLayout->count() == 1) displayOnEdition();
        else updateLibraryVisualisation();

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
    qDebug() << croppingButtons.size();
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
    int x = 770;
    int y = 130;
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
            confirmCropping->move(640, 180);
            confirmCropping->show();
            cancelCropping->move(520, 180);
            cancelCropping->show();
            connect(confirmCropping, SIGNAL(clicked()), actualCropping, SLOT(resizePicture()));
            connect(cancelCropping, SIGNAL(clicked()), this, SLOT(on_rogner_clicked()));
            connect(racourciEchapCropping, &QShortcut::activated, this, &ImagEdit::on_rogner_clicked);
            actualCropping->drawRectCropping(pix);
        }
        else {
            confirmCropping->hide();
            cancelCropping->hide();
            disconnect(racourciEchapCropping, &QShortcut::activated, this, &ImagEdit::on_rogner_clicked);
            actualCropping->deleteRectCropping();
            *pix = actualCropping->getPixmap();
            update();
        }
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

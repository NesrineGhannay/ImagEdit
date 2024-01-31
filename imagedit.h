#ifndef IMAGEDIT_H
#define IMAGEDIT_H

#include <QMainWindow>
#include <QPalette>

#include "filterarea.h"
#include "cropping.h"
#include <QStringList>
#include <QKeySequence>
#include <QShortcut>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>
#include <QListWidgetItem>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QPixmap>
#include <QIcon>
#include <QGridLayout>
#include <QShortcut>
#include <QKeySequence>
#include <QPropertyAnimation>
#include <iostream>


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class ImagEdit;
}
QT_END_NAMESPACE

class ImagEdit : public QMainWindow
{
    Q_OBJECT

public:
    ImagEdit(QWidget *parent = nullptr);
    ~ImagEdit();
    Cropping *croppingarera;



public slots:
    void on_open_clicked();
    void displayOnEdition();
    void on_filter_clicked();
    void on_rogner_clicked();
    void on_save_clicked();
    void on_save_under_clicked();
    void setupFilterButtonConnection();
    void setCurrentImage();


private slots:
    void on_importImage_clicked();

private:
    Ui::ImagEdit *ui;
    QString *path;
    QString *fileName;
    QPixmap *pix;
    QList<QPushButton*> croppingButtons;

    QList<QString> originalPaths;
    QShortcut *raccourciEnregistrer;
    QShortcut *raccourciOuvrir;
    QShortcut *racourciEchapCropping;
    int currentIndex;
    QRect *rect;
    Cropping *actualCropping;
    QPushButton *confirmCropping;
    QPushButton *cancelCropping;
    FilterArea *widgetFilter;
    QPushButton *boutonFiltre;
    bool isFilterVisible;
    bool clearImportPictureBtn = false;
    void addImageInLibrary();
    void updateLibraryVisualisation();
    const int gridSize = 30;
};
#endif

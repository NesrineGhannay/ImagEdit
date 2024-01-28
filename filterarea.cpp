#include "filterarea.h"
#include "ui_filterarea.h"
#include <iostream>
using namespace std;

FilterArea::FilterArea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FilterArea)
{
    ui->setupUi(this);
    connect(ui->NbFilterButton, SIGNAL(clicked()), this, SLOT(appliquerFiltreNoirEtBlanc()));
    connect(ui->OmbresChaudesFilterButton, SIGNAL(clicked()), this, SLOT(appliquerOmbresChaudesFilter()));
    connect(ui->LumFroidesFilterButton, SIGNAL(clicked()), this, SLOT(appliquerLumFroidesFilter()));
    connect(ui->SummerFiltreButton, &QPushButton::clicked, this, &FilterArea::appliquerSummerFiltre);
    connect(ui->luminositeSlider, SIGNAL(valueChanged(int)), this, SLOT(luminosityChanged()));
    connect(ui->saturationSlider, SIGNAL(valueChanged(int)), this, SLOT(saturationChanged()));

    //connect(parentWidget()->findChild<QPushButton*>("filter"), SIGNAL(clicked()), this, SLOT(on_filter_clicked()));
}


FilterArea::~FilterArea()
{
    delete ui;
}


void FilterArea::on_NbFilterButton_clicked()
{
    qDebug() << "NbFilterButton clicked";
    emit applyNbFilter();
}

void FilterArea::setLabel(QLabel *label) {

    labelSelected = label;
}

void FilterArea::appliquerFiltreNoirEtBlanc()
{
    isBlackAndWhiteFilter = true;
    if (!labelSelected->pixmap().isNull()) {

        QImage imageNoirEtBlanc(labelSelected->pixmap().toImage().size(), QImage::Format_Grayscale8);

        for (int y = 0; y < labelSelected->pixmap().toImage().height(); ++y) {
            for (int x = 0; x < labelSelected->pixmap().toImage().width(); ++x) {
                QRgb pixel = labelSelected->pixmap().toImage().pixel(x, y);
                int grayValue = qGray(pixel);
                imageNoirEtBlanc.setPixel(x, y, qRgb(grayValue, grayValue, grayValue));
            }
        }

        QPixmap pixmap = QPixmap::fromImage(imageNoirEtBlanc);


        labelSelected->setPixmap(pixmap);


    }
    else {
        qDebug() << "Erreur : Aucune image actuelle à traiter.";
    }
}

void FilterArea::on_LumFroidesFilterButton_clicked()
{

    if (!labelSelected->pixmap().isNull()) {

        QImage imageOmbresChaudes(labelSelected->pixmap().toImage().size(), QImage::Format_ARGB32);
        QColor ombresFroidesColor(27, 62, 121);
        qreal colorIntensity = 0.7;

        for (int y = 0; y < labelSelected->pixmap().toImage().height(); ++y) {
            for (int x = 0; x < labelSelected->pixmap().toImage().width(); ++x) {
                QRgb pixel = labelSelected->pixmap().toImage().pixel(x, y);
                QColor originalColor(pixel);
                QColor newColor = originalColor.toRgb();
                newColor = QColor::fromRgb(
                    qMin(255, int((newColor.red() * colorIntensity) + ombresFroidesColor.red() * (1.0 - colorIntensity))),
                    qMin(255, int(newColor.green() * colorIntensity + ombresFroidesColor.green() * (1.0 - colorIntensity))),
                    qMin(255, int(newColor.blue() * colorIntensity + ombresFroidesColor.blue() * (1.0 - colorIntensity)))
                    );
                newColor = newColor.lighter(140);
                imageOmbresChaudes.setPixel(x, y, newColor.rgb());
            }
        }
        QPixmap pixmap = QPixmap::fromImage(imageOmbresChaudes);
        labelSelected->setPixmap(pixmap);
    }
    else {
        qDebug() << "Erreur : Aucune image actuelle à traiter.";
    }

}

void FilterArea::appliquerOmbresChaudesFilter()
{
    qDebug() << "Appliquer filtre Ombres Chaudes";

    if (!labelSelected->pixmap().isNull()) {

        QImage imageOmbresChaudes(labelSelected->pixmap().toImage().size(), QImage::Format_ARGB32);
        QColor ombresChaudesColor(255, 170, 0);
        qreal colorIntensity = 0.8;

        for (int y = 0; y < labelSelected->pixmap().toImage().height(); ++y) {
            for (int x = 0; x < labelSelected->pixmap().toImage().width(); ++x) {
                QRgb pixel = labelSelected->pixmap().toImage().pixel(x, y);
                QColor originalColor(pixel);
                QColor newColor = originalColor.toRgb();
                newColor = QColor::fromRgb(
                    qMin(255, int((newColor.red() * colorIntensity) + ombresChaudesColor.red() * (1.0 - colorIntensity))),
                    qMin(255, int(newColor.green() * colorIntensity + ombresChaudesColor.green() * (1.0 - colorIntensity))),
                    qMin(255, int(newColor.blue() * colorIntensity + ombresChaudesColor.blue() * (1.0 - colorIntensity)))
                    );

                newColor = newColor.darker(100);
                imageOmbresChaudes.setPixel(x, y, newColor.rgb());
            }
        }
        QPixmap pixmap = QPixmap::fromImage(imageOmbresChaudes);
        labelSelected->setPixmap(pixmap);
    }
    else {
        qDebug() << "Erreur : Aucune image actuelle à traiter.";
    }
}

void FilterArea::luminosityChanged()
{
    qDebug() << __FUNCTION__ << "The event sender is" << sender();

    if (!labelSelected->pixmap().isNull()) {
        QImage imageLuminosityChanged(labelSelected->pixmap().toImage().size(), QImage::Format_ARGB32);


        int sliderValue = ui->luminositeSlider->value();
        for (int y = 0; y < labelSelected->pixmap().toImage().height(); ++y) {
            for (int x = 0; x < labelSelected->pixmap().toImage().width(); ++x) {
                QRgb pixel = labelSelected->pixmap().toImage().pixel(x, y);
                QColor originalColor(pixel);
                QColor newColor = originalColor.toRgb();
                newColor = newColor.lighter(100 + sliderValue/15);
                imageLuminosityChanged.setPixel(x, y, newColor.rgb());
            }
        }

        QPixmap pixmap = QPixmap::fromImage(imageLuminosityChanged);
        labelSelected->setPixmap(pixmap);
    } else {
        qDebug() << "Erreur : Aucune image actuelle à traiter.";
    }
}

void FilterArea::setIsFilter(bool filterBool) {
    isFilter = filterBool;
}

bool FilterArea::getIsFilter() {
    return isFilter;
}

bool FilterArea::getIsBlackAndWhiteFilter() {
    return isBlackAndWhiteFilter;
}

void FilterArea::appliquerSummerFiltre()
{
    qDebug() << "Appliquer filtre Summer";

    if (!labelSelected->pixmap().isNull()) {

        QImage imageSummer(labelSelected->pixmap().toImage().size(), QImage::Format_ARGB32);
        qreal saturationFactor = 2.5;

        for (int y = 0; y < labelSelected->pixmap().toImage().height(); ++y) {
            for (int x = 0; x < labelSelected->pixmap().toImage().width(); ++x) {
                QRgb pixel = labelSelected->pixmap().toImage().pixel(x, y);
                QColor originalColor(pixel);
                QColor newColor = originalColor.toRgb();

                int h, s, l;
                newColor.getHsl(&h, &s, &l);
                s = qMin(255, int(s * saturationFactor));
                newColor = QColor::fromHsl(h, s, l);
                newColor = newColor.lighter(110);
                imageSummer.setPixel(x, y, newColor.rgb());
            }
        }

        QPixmap pixmap = QPixmap::fromImage(imageSummer);
        labelSelected->setPixmap(pixmap);
    }
    else {
        qDebug() << "Erreur : Aucune image actuelle à traiter.";
    }
}

void FilterArea::saturationChanged()
{
    qDebug() << __FUNCTION__ << "The event sender is" << sender();

    if (!labelSelected->pixmap().isNull()) {
        QImage imageSaturationChanged(labelSelected->pixmap().toImage().size(), QImage::Format_ARGB32);
        qreal saturationFactor = 2.5;
        int sliderValue = ui->saturationSlider->value();

        for (int y = 0; y < labelSelected->pixmap().toImage().height(); ++y) {
            for (int x = 0; x < labelSelected->pixmap().toImage().width(); ++x) {
                QRgb pixel = labelSelected->pixmap().toImage().pixel(x, y);
                QColor originalColor(pixel);
                QColor newColor = originalColor.toRgb();
                int h, s, l;
                newColor.getHsl(&h, &s, &l);
                s = qMin(255, int(s + sliderValue/20));
                newColor = QColor::fromHsl(h, s, l);
                imageSaturationChanged.setPixel(x, y, newColor.rgb());
            }
        }

        QPixmap pixmap = QPixmap::fromImage(imageSaturationChanged);
        labelSelected->setPixmap(pixmap);
    } else {
        qDebug() << "Erreur : Aucune image actuelle à traiter.";
    }
}

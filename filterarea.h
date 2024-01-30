#ifndef FILTERAREA_H
#define FILTERAREA_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class FilterArea;
}

class FilterArea : public QWidget
{
    Q_OBJECT

public:
    explicit FilterArea(QWidget *parent = nullptr);
    ~FilterArea();

signals:
    void applyNbFilter();
    void applyOmbresCFilter();
    void applyLumFroidesFilter();
    void applySummerFilter();

public slots:
    void on_NbFilterButton_clicked();
    void appliquerFiltreNoirEtBlanc();
    void setLabel(QLabel *label);
    void appliquerOmbresChaudesFilter();
    void appliquerSummerFiltre();


private slots:
    void on_LumFroidesFilterButton_clicked();
    void luminosityChanged();
    void saturationChanged();


    void on_pushButton_clicked();

private:
    Ui::FilterArea *ui;
    QLabel *labelSelected;
    QImage originalImage;
    bool isFilter = false;
    bool isBlackAndWhiteFilter = false;

public:
    bool getIsFilter();
    void setIsFilter(bool filterBool);
    bool getIsBlackAndWhiteFilter();

};
#endif // FILTERAREA_H


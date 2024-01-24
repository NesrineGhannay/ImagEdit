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

public slots:
    void on_NbFilterButton_clicked();
    void appliquerFiltreNoirEtBlanc();
    void setLabel(QLabel *label);
    void on_LumFroidesFilterButton_clicked();
    void on_OmbresChaudesFilterButton_clicked();
    void appliquerOmbresChaudesFilter(); 
    void appliquerLumFroidesFilter();



private:
    Ui::FilterArea *ui;
    QLabel *labelSelected;
};
#endif // FILTERAREA_H


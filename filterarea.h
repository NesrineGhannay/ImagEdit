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
    void appliquerOmbresChaudesFilter();




private slots:
    void on_LumFroidesFilterButton_clicked();

<<<<<<< HEAD
    void luminosityChanged();

=======
    void on_OmbresChaudesFilterButton_clicked();
>>>>>>> aab4435daf9413a39cfcb7051f84fc9eabda9bda

private:
    Ui::FilterArea *ui;
    QLabel *labelSelected;
    QImage originalImage;
};
#endif // FILTERAREA_H


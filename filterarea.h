#ifndef FILTERAREA_H
#define FILTERAREA_H

#include <QWidget>

namespace Ui {
class FilterArea;
}

class FilterArea : public QWidget
{
    Q_OBJECT

public:
    explicit FilterArea(QWidget *parent = nullptr);
    ~FilterArea();

private:
    Ui::FilterArea *ui;
};

#endif // FILTERAREA_H

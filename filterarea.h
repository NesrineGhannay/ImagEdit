#ifndef FILTERAREA_H
#define FILTERAREA_H

#include <QWidget>

namespace Ui {
class Filterarea;
}

class Filterarea : public QWidget
{
    Q_OBJECT

public:
    explicit Filterarea(QWidget *parent = nullptr);
    ~Filterarea();

private:
    Ui::Filterarea *ui;
};

#endif // FILTERAREA_H

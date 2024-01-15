#ifndef ROGNERAREA_H
#define ROGNERAREA_H

#include <QWidget>

namespace Ui {
class RognerArea;
}

class RognerArea : public QWidget
{
    Q_OBJECT

public:
    explicit RognerArea(QWidget *parent = nullptr);
    ~RognerArea();

private:
    Ui::RognerArea *ui;
};

#endif // ROGNERAREA_H

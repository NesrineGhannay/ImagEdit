#ifndef SELECTIONAREA_H
#define SELECTIONAREA_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class selectionarea;
}

class selectionarea : public QWidget
{
    Q_OBJECT

public:
    explicit selectionarea(QWidget *parent = nullptr);
    ~selectionarea();

    bool getIsFilter();
    void setIsFilter(bool selectBool);

private:
    Ui::selectionarea *ui;

    QLabel *labelSelected;
    QImage originalImage;
    bool isSelect = false;
};

#endif // SELECTIONAREA_H

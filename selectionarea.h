#ifndef SELECTIONAREA_H
#define SELECTIONAREA_H

#include <QWidget>

namespace Ui {
class selectionarea;
}

class selectionarea : public QWidget
{
    Q_OBJECT

public:
    explicit selectionarea(QWidget *parent = nullptr);
    ~selectionarea();

private:
    Ui::selectionarea *ui;
};

#endif // SELECTIONAREA_H

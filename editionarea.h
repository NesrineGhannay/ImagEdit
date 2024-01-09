#ifndef EDITIONAREA_H
#define EDITIONAREA_H

#include <QWidget>

namespace Ui {
class EditionArea;
}

class EditionArea : public QWidget
{
    Q_OBJECT

public:
    explicit EditionArea(QWidget *parent = nullptr);
    ~EditionArea();

private:
    Ui::EditionArea *ui;
};

#endif // EDITIONAREA_H

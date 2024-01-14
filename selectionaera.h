#ifndef SELECTIONAERA_H
#define SELECTIONAERA_H

#include <QWidget>

namespace Ui {
class selectionaera;
}

class selectionaera : public QWidget
{
    Q_OBJECT

public:
    explicit selectionaera(QWidget *parent = nullptr);
    ~selectionaera();

private:
    Ui::selectionaera *ui;
};

#endif // SELECTIONAERA_H

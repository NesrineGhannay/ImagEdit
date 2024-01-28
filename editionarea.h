#ifndef EDITIONAREA_H
#define EDITIONAREA_H

namespace Ui {
class EditionArea;
}

class EditionArea : public QWidget, private Ui::EditionArea
{
    Q_OBJECT

public:
    explicit EditionArea(QWidget *parent = nullptr);

};


#endif // EDITIONAREA_H

#ifndef LIBRARYAREA_H
#define LIBRARYAREA_H

#include <QWidget>

namespace Ui {
class LibraryArea;
}

class LibraryArea : public QWidget
{
    Q_OBJECT

public:
    explicit LibraryArea(QWidget *parent = nullptr);
    ~LibraryArea();

private:
    Ui::LibraryArea *ui;
};

#endif // LIBRARYAREA_H

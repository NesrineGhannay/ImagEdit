#ifndef TOOLBOXAREA_H
#define TOOLBOXAREA_H

#include <QWidget>

namespace Ui {
class ToolboxArea;
}

class ToolboxArea : public QWidget
{
    Q_OBJECT

public:
    explicit ToolboxArea(QWidget *parent = nullptr);
    ~ToolboxArea();

private:
    Ui::ToolboxArea *ui;
};

#endif // TOOLBOXAREA_H

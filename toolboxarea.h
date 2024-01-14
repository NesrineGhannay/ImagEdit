#ifndef TOOLBOXAREA_H
#define TOOLBOXAREA_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

namespace Ui {
class ToolboxArea;
}

class ToolboxArea : public QWidget
{
    Q_OBJECT

public:
    explicit ToolboxArea(QWidget *parent = nullptr);
    ~ToolboxArea();

private slots:
    void on_filter_clicked();

private slots:
    void on_selection_clicked();

private:
    Ui::ToolboxArea *ui;

};

#endif // TOOLBOXAREA_H

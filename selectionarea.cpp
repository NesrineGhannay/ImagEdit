#include "selectionarea.h"
#include "ui_selectionarea.h"

selectionarea::selectionarea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectionarea)
{
    ui->setupUi(this);

    connect(ui->rectangleButton, &QPushButton::clicked, this, &selectionarea::selectRectangle);
    connect(ui->ellipseButton, &QPushButton::clicked, this, &selectionarea::selectEllipse);
    connect(ui->etoileButton, &QPushButton::clicked, this, &selectionarea::selectStar);
    connect(ui->triangleButton, &QPushButton::clicked, this, &selectionarea::selectTriangle);
    connect(ui->libreButton, &QPushButton::clicked, this, &selectionarea::selectLibre);

}

void selectionarea::setIsFilter(bool selectBool) {
    isSelect = selectBool;
}

bool selectionarea::getIsFilter() {
    return isSelect;
}

void selectionarea::on_pushButton_clicked()
{
    this->close();
}

void selectionarea::selectRectangle()
{
    qDebug() << "Selection Rectangle";
}

void selectionarea::selectEllipse()
{
    qDebug() << "Selection Ellipse";
}

void selectionarea::selectStar()
{
    qDebug() << "Selection Etoile";
}

void selectionarea::selectTriangle()
{
    qDebug() << "Selection Triangle";
}

void selectionarea::selectLibre()
{
    qDebug() << "Selection Libre";
}



selectionarea::~selectionarea()
{
    delete ui;
}

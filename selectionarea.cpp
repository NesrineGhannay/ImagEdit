#include "selectionarea.h"
#include "ui_selectionarea.h"

selectionarea::selectionarea(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectionarea)
{
    ui->setupUi(this);

    /*currentRect = currentRect;;
    m_resizeHandlePressed = false;
    setFocusPolicy(Qt::StrongFocus);*/

    connect(ui->rectangleButton, &QPushButton::clicked, this, &selectionarea::selectRectangle);
    connect(ui->ellipseButton, &QPushButton::clicked, this, &selectionarea::selectEllipse);
    connect(ui->etoileButton, &QPushButton::clicked, this, &selectionarea::selectStar);
    connect(ui->triangleButton, &QPushButton::clicked, this, &selectionarea::selectTriangle);
    connect(ui->libreButton, &QPushButton::clicked, this, &selectionarea::selectLibre);

}

/*
//Créé la poignée
QRect selectionarea::resizeHandle() const
{
    QPoint br = currentRect.bottomRight();
    return QRect(br - QPoint(resizeHandleWidth, resizeHandleWidth), br);
}

//Quand on clique sur le boutton entrée ca rogne l'image
void selectionarea::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Return)
        selectPicture();
    update();
}

//C'est celle-ci qui coupe
void selectionarea::selectPicture() {
    this->setPixmap(cutImage());
}

//Celle qui permet de redimensionner la widget du dessus
void selectionarea::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    m_resizeHandlePressed = this->resizeHandle().contains(event->position().toPoint());
    if (m_resizeHandlePressed)
        m_mousePressOffset = currentRect.bottomRight() - event->position().toPoint();
    else
        m_mousePressOffset = event->position().toPoint() - currentRect.topLeft();


}

//C'est celle qui va mettre à jour les dimension selectionné avec la widget (dans cropping elle coupé l'image)
QPixmap selectionarea::cutImage() {
    QImage newImage = pixImage.toImage();

    int marge_lateral = (this->width() - newImage.width())/2;
    int marge_vertical = (this->height() - newImage.height())/2;

    for(int i = 0; i < currentRect.left()-marge_lateral; i++) {
        for(int j = 0; j < newImage.height(); j++) {
            newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.right()-marge_lateral; i < newImage.width(); i++) {
        for(int j = 0; j < newImage.height(); j++) {
            newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.topLeft().x() - marge_lateral; i < currentRect.topRight().x() + marge_lateral; i++) {
        for(int j = 0; j < currentRect.topLeft().y() - marge_vertical; j++) {
            newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }

    for(int i = currentRect.bottomLeft().x() - marge_lateral; i < currentRect.topRight().x() + marge_lateral; i++) {
        for(int j = currentRect.bottomLeft().y() - marge_vertical; j < newImage.height(); j++) {
            newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }


    return QPixmap::fromImage(newImage);
}

void selectionarea::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    if (m_resizeHandlePressed) {
        currentRect = QRect(currentRect.topLeft(), event->position().toPoint() + m_mousePressOffset);

    } else {
        currentRect.moveTopLeft(event->position().toPoint() - m_mousePressOffset);
    }
    update();
}

//dessine le rectangle de recadrage et la poignée de redimensionnement
void selectionarea::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue, 2));
    QColor grayWithAlpha = QColor(0, 0, 128, 128);
    painter.setBrush(QBrush(grayWithAlpha));
    painter.drawRect(currentRect);
    painter.drawRect(resizeHandle());
}

// initialise le rectangle de recadrage autour de l'image centrée dans le widget
void selectionarea::drawRectSelect(QPixmap *pix) {
    pixImage = *pix;
    currentRect = QRect(this->width()/2-pix->width()/2,
                        this->height()/2-pix->height()/2,
                        pix->width(),
                        pix->height()
                        );
    isCropping = true;
    update();
    releaseKeyboard();
}

//réinitialise le rectangle de recadrage, met à jour le widget pour refléter les changements
//et indique que le processus de recadrage n'est plus en cours
void selectionarea::deleteRectSelect() {
    currentRect = QRect();
    update();
    isCropping = false;
}*/

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

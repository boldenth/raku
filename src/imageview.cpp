#include "imageview.h"
#include "ui_imageview.h"
#include "iohandler.h"

#include <QMenu>
#include <QLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QSizeGrip>
#include <QDialog>

#include <QDebug>

ImageView::ImageView(QWidget *parent, QString imgFile) :
    QDockWidget(parent, Qt::SubWindow),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
    this->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    this->setAllowedAreas(Qt::TopDockWidgetArea);

    this->image = new Image(imgFile);
    connect(image, &Image::mouseEvent, this, &ImageView::mouseEvent_image);

    this->view = new QGraphicsView();
    this->scene = new QGraphicsScene();

    // scene add Image class which inherits QGraphicsPixmapItem
    scene->addItem(image);
    scene->setSceneRect(scene->itemsBoundingRect());
    view->setScene(scene);
    view->scale(2, 2);
    QSize size = scene->itemsBoundingRect().size().toSize() * 2;
    view->setFixedSize(size.width() + 2, size.height() + 2);

//
//    QWidget *internal_widget = new QWidget();
//    QVBoxLayout *layout = new QVBoxLayout(internal_widget);
//    layout->setContentsMargins(QMargins());
//    layout->setSpacing(0);
//    layout->addWidget(view);
//    layout->addWidget(new QSizeGrip(this->view), 0, Qt::AlignBottom | Qt::AlignRight);
//    internal_widget->setLayout(layout);
//    this->setWidget(internal_widget);
//

    this->setWidget(this->view);

    // TODO: make random (but light colors)? for each new window so colors are different for images
    int red = 100, green = 150, blue = 205;
    QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(red)
            .arg(green)
            .arg(blue);
    this->setStyleSheet(stylesheet);

    //connect(this->ui->dockWidget, &QDockWidget::dockLocationChanged, this, &ImageView::close);
    this->setMouseTracking(false);
    this->setAttribute(Qt::WA_Hover);

    this->setWindowTitle(imgFile.split("/").last());

    // TODO: add this to next declaration when working
    connect(this->image, &Image::mouseEvent, this, &ImageView::paintOnImage);

    installEventFilter(this);
}

ImageView::ImageView(QWidget *parent, int width, int height, int ncolors) :
    QDockWidget(parent, Qt::SubWindow),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
    this->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    this->setAllowedAreas(Qt::TopDockWidgetArea);

    this->image = new Image(width, height, ncolors);
    connect(image, &Image::mouseEvent, this, &ImageView::mouseEvent_image);

    this->view = new QGraphicsView();
    this->scene = new QGraphicsScene();

    // scene add Image class which inherits QGraphicsPixmapItem
    scene->addItem(image);
    scene->setSceneRect(scene->itemsBoundingRect());
    view->setScene(scene);
    view->scale(2, 2);
    QSize size = scene->itemsBoundingRect().size().toSize() * 2;
    view->setFixedSize(size.width() + 2, size.height() + 2);

    this->setWidget(this->view);

    // TODO: make random (but light colors)? for each new window so colors are different for images
    int red = 200, green = 50, blue = 105;
    QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(red)
            .arg(green)
            .arg(blue);
    this->setStyleSheet(stylesheet);

    //connect(this->ui->dockWidget, &QDockWidget::dockLocationChanged, this, &ImageView::close);
    this->setMouseTracking(false);
    this->setAttribute(Qt::WA_Hover);

    int n = 1;
    this->setWindowTitle(QString("new image %1").arg(n));

    //installEventFilter(this);
}

ImageView::~ImageView()
{
    // emit signal for editor to change focused image
    delete image;
    delete scene;
    delete view;
    delete ui;
}

void ImageView::closeEvent(QCloseEvent *event) {
    emit shouldDeletePalette();
    // emit decrease index
    QDockWidget::closeEvent(event);
}

void ImageView::configureGrid(int width, int height, QColor color) {
    //
    this->gridWidth = width;
    this->gridHeight = height;
    this->gridColor = color;
    //this->showGrid = false;// temp hack
    drawGrid(true);// TODO: make sure this doesn't toggle
}

void ImageView::drawGrid(bool visible) {
    this->showGrid = visible;// toggle grid visibility

    for (QGraphicsLineItem* item : gridlines) {
        if (item && item->scene()) {
            item->scene()->removeItem(item);
        }
        delete item;
    }

    int w = this->image->pixmap().width();
    int h = this->image->pixmap().height();

    QPen pen(this->gridColor);
    pen.setWidth(0);

    for (int x = 0; x <= w; x += this->gridWidth) {
        //
        QGraphicsLineItem *line = scene->addLine(x, 0, x, h, pen);
        line->setVisible(showGrid);
        gridlines.append(line);
    }
    for (int y = 0; y <= h; y += this->gridHeight) {
        //
        QGraphicsLineItem *line = scene->addLine(0, y, w, y, pen);
        line->setVisible(showGrid);
        gridlines.append(line);
    }
}

// TODO: check whether inside scene or not? or just activate on titleBarWidget?
void ImageView::mousePressEvent(QMouseEvent *event) {
    //
    if (!(event->buttons() & Qt::LeftButton)) return;

    if (event->localPos().y() > 24) {
        // clicking on the scene
        //qDebug() << event->type();
        //emit paintOnImage(event->localPos().y() - 22, event->localPos().x());
        return;
    }

    this->origin = event->globalPos();

    setCursor(Qt::ClosedHandCursor);

    //this->scene->
    //QGraphicsScene::mousePressEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {
    //
    if (!(event->buttons() & Qt::LeftButton)) return;

    //qDebug() << "globalPos" << event->globalPos();

    const QPoint delta = event->globalPos() - this->origin;

    int x = this->x() + delta.x();
    x = x > 0 ? x : this->x();

    int y = this->y() + delta.y();
    y = y > 0 ? y : this->y();

    // TODO: figure out how to only move when cursor is over the widget
    //       in specific direction
    //       or let go when not over dock widget
    //if (event->localPos().x() < this->x()) x = 0;
    //if (event->localPos().y() < this->y()) y = 0;

    this->move(x, y);
    this->origin = event->globalPos();
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {
    //
    unsetCursor();
}

void ImageView::hoverEnterEvent(QHoverEvent *event) {
    //
    qDebug() << "hoverEnter";
    setCursor(Qt::OpenHandCursor);
}

void ImageView::hoverLeaveEvent(QHoverEvent *event) {
    //
    qDebug() << "hoverLeave";
    unsetCursor();
}

void ImageView::mouseEvent_image(QGraphicsSceneMouseEvent *event, Image *img) {
    //
    //qDebug() << "mouseEvent_image";
}






















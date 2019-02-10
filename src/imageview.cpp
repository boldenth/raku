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
    connect(image, &Image::mouseEvent, this, &ImageView::mouseEvent_image);/*map_item, SIGNAL(mouseEvent(QGraphicsSceneMouseEvent*,MapPixmapItem*)),
            this, SLOT(mouseEvent_map(QGraphicsSceneMouseEvent*,MapPixmapItem*)));*/

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

    //installEventFilter(this);
}

ImageView::~ImageView()
{
    delete image;
    delete scene;
    delete view;
    delete ui;
}

void ImageView::closeEvent(QCloseEvent *event) {
    //~ImageView;
    emit shouldDeletePalette();
    // emit decrease index
    QDockWidget::closeEvent(event);
    //saveJASCPal(this->image->path + "_palette.pal", *this->image->palette);
}

// TODO: check whether inside scene or not? or just activate on titleBarWidget?
void ImageView::mousePressEvent(QMouseEvent *event) {
    //
    if (!(event->buttons() & Qt::LeftButton)) return;

    if (event->localPos().y() > 22) {
        // clicking on the scene
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

    //if (event->localPos().x() <= 0 || event->localPos().y() <= 0) return;

    const QPoint delta = event->globalPos() - origin;
    this->move(this->x() + delta.x(), this->y() + delta.y());
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
    qDebug() << "mouseEvent_image";
}
/*
void ImageView::mousePressEvent_titleBar(QMouseEvent *event) {
    //
    qDebug() << "mousePressEvent_titleBar";
}
*/





















#include "imageview.h"
#include "ui_imageview.h"
#include "iohandler.h"

#include <QMenu>
#include <QLayout>
#include <QMenuBar>
#include <QToolBar>

#include <QDebug>

ImageView::ImageView(QWidget *parent, QString imgFile) :
    QDockWidget(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);
    this->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);

    this->image = new Image(imgFile);
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
    int red = 100, green = 150, blue = 205;
    QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(red)
            .arg(green)
            .arg(blue);
    this->setStyleSheet(stylesheet);

    //connect(this->ui->dockWidget, &QDockWidget::dockLocationChanged, this, &ImageView::close);
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
    QDockWidget::closeEvent(event);
    //saveJASCPal(this->image->path + "palette.pal", *this->image->palette);
}




























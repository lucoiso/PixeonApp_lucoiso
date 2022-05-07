#include "pixeoncustomview.h"
#include "pixeontoolbar.h"
#include "ui_customview.h"
#include "HelperFunctions.h"

#include <QGraphicsView>

CustomView::CustomView(QWidget *parent, const QString FileName) :
    QWidget(parent),
    ui(new Ui::CustomView)
{
    ui->setupUi(this);

    QPixmap NewImage(FileName.count() != 0 ? FileName : ":/Pixeon/Assets/Placeholder.jpeg");
    QGraphicsScene* NewScene = new QGraphicsScene();
    NewScene->addPixmap(NewImage.scaled(QSize(parent->width(), parent->height()), Qt::AspectRatioMode::KeepAspectRatioByExpanding));
    ui->graphicsView->setScene(NewScene);

    ui->horizontalLayout->insertWidget(0, new PixeonToolbar("Custom PixeonToolbar", this));
}

CustomView::~CustomView()
{
    delete ui;
}

void CustomView::ChangeImage()
{
    const int Height = ui->graphicsView->height();
    const int Width = ui->graphicsView->width();

    const QString ImagePath = Helpers::LoadNewImageFile(this);
    if (ImagePath.count() > 0)
    {
        QGraphicsScene* NewScene = new QGraphicsScene();
        NewScene->addPixmap(QPixmap(ImagePath).scaled(QSize(Width, Height), Qt::AspectRatioMode::KeepAspectRatioByExpanding));
        ui->graphicsView->setScene(NewScene);
    }
}

void CustomView::RemoveImage()
{
    const int Height = ui->graphicsView->height();
    const int Width = ui->graphicsView->width();

    QGraphicsScene* NewScene = new QGraphicsScene();
    NewScene->addPixmap(QPixmap(":/Pixeon/Assets/Placeholder.jpeg").scaled(QSize(Width, Height), Qt::AspectRatioMode::KeepAspectRatioByExpanding));
    ui->graphicsView->setScene(NewScene);
}


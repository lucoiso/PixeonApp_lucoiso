#include "pixeoncustomview.h"
#include "pixeontoolbar.h"
#include "ui_customview.h"
#include "HelperFunctions.h"

#include <QGraphicsView>
#include <QRgb>

CustomView::CustomView(QWidget *parent, const QString FileName) :
    QWidget(parent),
    ui(new Ui::CustomView)
  , CurrentBrightnessFactor(100)
{
    ui->setupUi(this);

    QPixmap NewImage(FileName.count() != 0 ? FileName : ":/Pixeon/Assets/Placeholder.jpeg");

    UpdateGraphicsView(NewImage);
    ui->horizontalLayout->insertWidget(0, new PixeonToolbar("Custom PixeonToolbar", this));
}

CustomView::~CustomView()
{
    delete ui;
}

void CustomView::ChangeImage()
{
    const QString ImagePath = Helpers::LoadNewImageFile(this);
    if (ImagePath.count() > 0)
    {
        OriginalImage = QImage(ImagePath);
        CurrentBrightnessFactor = 0;
        UpdateGraphicsView(QPixmap::fromImage(OriginalImage));
    }    
}

void CustomView::RemoveImage()
{
    OriginalImage = QImage();
    CurrentBrightnessFactor = 0;
    UpdateGraphicsView(QPixmap(":/Pixeon/Assets/Placeholder.jpeg"));
}

void CustomView::UpdateGraphicsView(const QPixmap Image)
{
    QGraphicsScene* NewScene = new QGraphicsScene(this);
    NewScene->addPixmap(Image);
    ui->graphicsView->setScene(NewScene);
}

void CustomView::ZoomIn()
{
    if (!OriginalImage.isNull())
    {
        ui->graphicsView->scale(1.25f, 1.25f);
    }
}

void CustomView::ZoomOut()
{
    if (!OriginalImage.isNull())
    {
        ui->graphicsView->scale(0.75f, 0.75f);
    }
}

void CustomView::RotateLeft()
{
    if (!OriginalImage.isNull())
    {
        ui->graphicsView->rotate(-90);
    }
}

void CustomView::RotateRight()
{
    if (!OriginalImage.isNull())
    {
        ui->graphicsView->rotate(90);
    }
}

void CustomView::BrightnessUp()
{
    QImage CurrentImage = OriginalImage;
    if (!CurrentImage.isNull())
    {
        CurrentBrightnessFactor += 5;
        for (int y = 0; y < CurrentImage.height(); ++y)
        {
            for (int x = 0; x < CurrentImage.width(); ++x)
            {
                CurrentImage.setPixelColor(x, y, CurrentImage.pixelColor(x, y).lighter(100 + CurrentBrightnessFactor));
            }
        }

        UpdateGraphicsView(QPixmap::fromImage(CurrentImage));
    }
}

void CustomView::BrightnessDown()
{
    QImage CurrentImage = OriginalImage;
    if (!CurrentImage.isNull())
    {
        CurrentBrightnessFactor -= 5;
        for (int y = 0; y < CurrentImage.height(); ++y)
        {
            for (int x = 0; x < CurrentImage.width(); ++x)
            {
                CurrentImage.setPixelColor(x, y, CurrentImage.pixelColor(x, y).lighter(100 + CurrentBrightnessFactor));
            }
        }

        UpdateGraphicsView(QPixmap::fromImage(CurrentImage));
    }
}

void CustomView::ContrastUp()
{
}

void CustomView::ContrastDown()
{
}

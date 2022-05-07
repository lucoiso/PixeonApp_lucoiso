#include "pixeoncustomview.h"
#include "pixeontoolbar.h"
#include "ui_pixeoncustomview.h"
#include "HelperFunctions.h"

#include <QGraphicsView>
#include <QRgb>

CustomView::CustomView(QWidget *parent, const QString FileName) :
    QWidget(parent),
    ui(new Ui::CustomView)
  , CurrentBrightnessFactor(100)
  , CurrentContrastFactor(0)
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
        CurrentBrightnessFactor = 100;
        UpdateGraphicsView(QPixmap::fromImage(OriginalImage));
        ui->graphicsView->resetTransform();
    }
}

void CustomView::RemoveImage()
{
    OriginalImage = QImage();
    CurrentBrightnessFactor = 100;
    UpdateGraphicsView(QPixmap(":/Pixeon/Assets/Placeholder.jpeg"));
    ui->graphicsView->resetTransform();
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

void CustomView::UpdatePixelColors(std::function<void(QImage&, const int, const int)> Predicate)
{
    QImage NewImage = OriginalImage.convertToFormat(QImage::Format_ARGB32);
    if (!NewImage.isNull())
    {
        for (int y = 0; y < NewImage.height(); ++y)
        {
            for (int x = 0; x < NewImage.width(); ++x)
            {
                Predicate(NewImage, x, y);
            }
        }

        UpdateGraphicsView(QPixmap::fromImage(NewImage));
    }
}

#define BRIGHTNESS_LAMBDA \
    [&] (QImage& Image, const int x, const int y) -> void \
    { \
        Image.setPixelColor(x, y, Image.pixelColor(x, y).lighter(CurrentBrightnessFactor)); \
    } \

void CustomView::BrightnessUp()
{
    CurrentBrightnessFactor += 5;
    UpdatePixelColors(BRIGHTNESS_LAMBDA);
}

void CustomView::BrightnessDown()
{
    CurrentBrightnessFactor -= 5;
    ;
    UpdatePixelColors(BRIGHTNESS_LAMBDA);
}

#define CONTRAST_LAMBDA \
    [&] (QImage& Image, const int x, const int y) -> void \
    { \
        QColor NewPixelColor = Image.pixelColor(x, y); \
        int Red, Green, Blue; \
        NewPixelColor.getRgb(&Red, &Green, &Blue); \
        const QRgb NewRgb = qRgb(std::clamp(Red + CurrentContrastFactor, 0, 255), \
                                 std::clamp(Green + CurrentContrastFactor, 0, 255), \
                                 std::clamp(Blue + CurrentContrastFactor, 0, 255)); \
        Image.setPixelColor(x, y, NewRgb); \
    } \

void CustomView::ContrastUp()
{
    CurrentContrastFactor -= 5;
    UpdatePixelColors(CONTRAST_LAMBDA);
}

void CustomView::ContrastDown()
{
    CurrentContrastFactor += 5;
    UpdatePixelColors(CONTRAST_LAMBDA);
}

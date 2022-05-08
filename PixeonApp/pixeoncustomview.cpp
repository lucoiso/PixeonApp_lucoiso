#include "pixeoncustomview.h"
#include "pixeontoolbar.h"
#include "HelperFunctions.h"

#include "ui_pixeoncustomview.h"

#include <QGraphicsView>
#include <QRgb>
#include <QTabWidget>

PixeonCustomView::PixeonCustomView(QWidget* parent, QTabWidget* OwnerTab, const QString& FileName) :
    QWidget(parent),
    ParentTab(OwnerTab)
  , ui(new Ui::PixeonCustomView)
  , CurrentBrightnessFactor(100)
  , CurrentContrastFactor(0)
{
    assert(OwnerTab != nullptr); // This widget is intended to be used with a TabWidget. Ensure that you pass the owner tab.

    ui->setupUi(this);

    QPixmap NewImage(FileName.count() != 0 ? FileName : ":/Pixeon/Assets/Placeholder.jpeg");

    UpdateGraphicsView(NewImage);
    ui->horizontalLayout->insertWidget(0, new PixeonToolbar("Custom PixeonToolbar", this));
}

PixeonCustomView::~PixeonCustomView()
{
    delete ui;
}

void PixeonCustomView::ChangeImage()
{
    const QString ImagePath = Helpers::LoadNewImageFile(this);
    if (ImagePath.count() > 0)
    {
        OriginalImage = QImage(ImagePath);
        CurrentBrightnessFactor = 100;
        UpdateGraphicsView(QPixmap::fromImage(OriginalImage));
        ui->graphicsView->resetTransform();

        ParentTab->setTabText(ParentTab->currentIndex(), ImagePath);
    }
}

void PixeonCustomView::RemoveImage()
{
    OriginalImage = QImage();
    CurrentBrightnessFactor = 100;
    UpdateGraphicsView(QPixmap(":/Pixeon/Assets/Placeholder.jpeg"));
    ui->graphicsView->resetTransform();

    ParentTab->setTabText(ParentTab->currentIndex(), "Empty");
}

void PixeonCustomView::UpdateGraphicsView(const QPixmap Image)
{
    QGraphicsScene* NewScene = new QGraphicsScene(this);
    NewScene->addPixmap(Image);
    ui->graphicsView->setScene(NewScene);
}

void PixeonCustomView::ZoomIn()
{
    if (!OriginalImage.isNull())
    {
        ui->graphicsView->scale(1.25f, 1.25f);
    }
}

void PixeonCustomView::ZoomOut()
{
    if (!OriginalImage.isNull())
    {
        ui->graphicsView->scale(0.75f, 0.75f);
    }
}

void PixeonCustomView::RotateLeft()
{
    if (!OriginalImage.isNull())
    {
        ui->graphicsView->rotate(-90);
    }
}

void PixeonCustomView::RotateRight()
{
    if (!OriginalImage.isNull())
    {
        ui->graphicsView->rotate(90);
    }
}

#define COLORUPDATE \
    [&] (QImage& Image, const int x, const int y) -> void \
    { \
        QColor NewPixelColor = Image.pixelColor(x, y); \
        int Red, Green, Blue; \
        NewPixelColor.getRgb(&Red, &Green, &Blue); \
        const QRgb NewRgb = qRgb(std::clamp(Red + CurrentContrastFactor, 0, 255), \
                                 std::clamp(Green + CurrentContrastFactor, 0, 255), \
                                 std::clamp(Blue + CurrentContrastFactor, 0, 255)); \
        Image.setPixelColor(x, y, QColor(NewRgb).lighter(CurrentBrightnessFactor)); \
    } \

void PixeonCustomView::BrightnessUp()
{
    CurrentBrightnessFactor += 5;
    UpdatePixelColors(COLORUPDATE);
}

void PixeonCustomView::BrightnessDown()
{
    CurrentBrightnessFactor -= 5;
    UpdatePixelColors(COLORUPDATE);
}

void PixeonCustomView::ContrastUp()
{
    CurrentContrastFactor -= 5;
    UpdatePixelColors(COLORUPDATE);
}

void PixeonCustomView::ContrastDown()
{
    CurrentContrastFactor += 5;
    UpdatePixelColors(COLORUPDATE);
}

void PixeonCustomView::UpdatePixelColors(std::function<void(QImage&, const int, const int)> Function)
{
    QImage NewImage = OriginalImage.convertToFormat(QImage::Format_ARGB32);
    if (!NewImage.isNull())
    {
        for (int y = 0; y < NewImage.height(); ++y)
        {
            for (int x = 0; x < NewImage.width(); ++x)
            {
                Function(NewImage, x, y);
            }
        }

        UpdateGraphicsView(QPixmap::fromImage(NewImage));
    }
}
#undef COLORUPDATE

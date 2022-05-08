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
    // This widget is intended to be used with a TabWidget. Ensure that you pass the owner tab.
    assert(OwnerTab != nullptr);

    ui->setupUi(this);

    QPixmap NewImage(FileName.count() != 0 ? FileName : ":/Pixeon/Assets/Placeholder.jpeg");

    Helpers::UpdateGraphicsView(this, ui->graphicsView, NewImage);
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
        Helpers::UpdateGraphicsView(this, ui->graphicsView, QPixmap::fromImage(OriginalImage));
        ui->graphicsView->resetTransform();

        ParentTab->setTabText(ParentTab->currentIndex(), ImagePath);

        qDebug() << __func__ << "- New image loaded:" << ImagePath;
    }
}

void PixeonCustomView::RemoveImage()
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

    OriginalImage = QImage();
    CurrentBrightnessFactor = 100;
    Helpers::UpdateGraphicsView(this, ui->graphicsView, QPixmap(":/Pixeon/Assets/Placeholder.jpeg"));
    ui->graphicsView->resetTransform();

    ParentTab->setTabText(ParentTab->currentIndex(), "Empty");
}

void PixeonCustomView::ZoomIn()
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

    if (!OriginalImage.isNull())
    {
        ui->graphicsView->scale(1.25f, 1.25f);
    }
}

void PixeonCustomView::ZoomOut()
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

    if (!OriginalImage.isNull())
    {
        ui->graphicsView->scale(0.75f, 0.75f);
    }
}

void PixeonCustomView::RotateLeft()
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

    if (!OriginalImage.isNull())
    {
        ui->graphicsView->rotate(-90);
    }
}

void PixeonCustomView::RotateRight()
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

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
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

    CurrentBrightnessFactor += 5;
    UpdatePixelColors(COLORUPDATE);
}

void PixeonCustomView::BrightnessDown()
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

    CurrentBrightnessFactor -= 5;
    UpdatePixelColors(COLORUPDATE);
}

void PixeonCustomView::ContrastUp()
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

    CurrentContrastFactor -= 5;
    UpdatePixelColors(COLORUPDATE);
}

void PixeonCustomView::ContrastDown()
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

    CurrentContrastFactor += 5;
    UpdatePixelColors(COLORUPDATE);
}

void PixeonCustomView::UpdatePixelColors(std::function<void(QImage&, const int, const int)> Function)
{
    qDebug() << ParentTab->tabText(ParentTab->currentIndex()) << "-" << __func__;

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

        Helpers::UpdateGraphicsView(this, ui->graphicsView, QPixmap::fromImage(NewImage));
    }
}
#undef COLORUPDATE

#pragma once

#include <QWidget>

class QTabWidget;

namespace Ui
{
    class PixeonCustomView;
}

class PixeonCustomView : public QWidget
{
    Q_OBJECT

public:
    // Note that this widget have both parent and TabOwner: For some reason, the casting to QTabWidget from QWidget was failing,
    // so i decided do duplicate the reference and use the main window as parent
    explicit PixeonCustomView(QTabWidget* TabOwner, QWidget* parent = nullptr, const QString& FileName = QString());
    ~PixeonCustomView();

    // START OF IMAGE ADJUSTMENT FUNCTIONS
    void ChangeImage();
    void RemoveImage();

    void ZoomIn();
    void ZoomOut();

    void RotateLeft();
    void RotateRight();

    void BrightnessUp();
    void BrightnessDown();

    void ContrastUp();
    void ContrastDown();
    // END OF IMAGE ADJUSTMENT FUNCTIONS

protected:
    /* Perform the passed function on each image pixel to do adjustments like brightness and contrast changes */
    void UpdatePixelColors(std::function<void(QImage&, const int, const int)> Function);

    /* Owning tab widget */
    QTabWidget* ParentTab;

private:
    Ui::PixeonCustomView* ui;

    /* Image handle to use when blending image effects */
    QImage OriginalImage;

    /* Current brightness factor to use when applying additional effects */
    int CurrentBrightnessFactor;

    /* Current contrast factor to use when applying additional effects */
    int CurrentContrastFactor;
};

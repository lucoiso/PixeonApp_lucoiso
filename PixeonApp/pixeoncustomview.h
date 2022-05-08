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
    explicit PixeonCustomView(QWidget* parent = nullptr, QTabWidget* TabOwner = nullptr, const QString& FileName = QString());
    ~PixeonCustomView();

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

protected:
    void UpdateGraphicsView(const QPixmap Image);

    void UpdatePixelColors(std::function<void(QImage&, const int, const int)> Function);

    QTabWidget* ParentTab;

private:
    Ui::PixeonCustomView* ui;
    QImage OriginalImage;

    int CurrentBrightnessFactor;
    int CurrentContrastFactor;
};

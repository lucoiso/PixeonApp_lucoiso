#pragma once

#include <QWidget>

class QTabWidget;

namespace Ui
{
    class CustomView;
}

class CustomView : public QWidget
{
    Q_OBJECT

public:
    explicit CustomView(QWidget* parent = nullptr, QTabWidget* TabOwner = nullptr, const QString& FileName = QString());
    ~CustomView();

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

    void UpdatePixelColors(std::function<void(QImage&, const int, const int)> Predicate);

    QTabWidget* ParentTab;

private:
    Ui::CustomView* ui;
    QImage OriginalImage;

    int CurrentBrightnessFactor;
    int CurrentContrastFactor;
};

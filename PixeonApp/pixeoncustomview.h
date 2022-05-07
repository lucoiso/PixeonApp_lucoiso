#pragma once

#include <QWidget>

namespace Ui {
class CustomView;
}

class CustomView : public QWidget
{
    Q_OBJECT

public:
    explicit CustomView(QWidget *parent = nullptr, const QString FileName = QString());
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

private:
    Ui::CustomView *ui;
    QImage OriginalImage;

    void UpdateGraphicsView(const QPixmap Image);

    void UpdatePixelColors(std::function<void(QImage&, const int, const int)> Predicate);

    int CurrentBrightnessFactor;
    int CurrentContrastFactor;
};

#ifndef PIXEONCUSTOMVIEW_H
#define PIXEONCUSTOMVIEW_H

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

private:
    Ui::CustomView *ui;
};

#endif // PIXEONCUSTOMVIEW_H
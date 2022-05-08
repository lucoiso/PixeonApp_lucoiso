#include "pixeontoolbar.h"
#include "pixeoncustomview.h"
#include "mainwindow.h"

PixeonToolbar::PixeonToolbar(const QString& title, QWidget* parent)
    : QToolBar(title, parent)
{
    assert(GetParentAsCustomView() != nullptr); // This toolbar is intended to be used inside a Custom View widget, ensure that you pass a valid PixeonCustomView as parent

    const QString Prefix = ":/Pixeon/Assets/";

    QAction* AddImage = new QAction(QIcon::fromTheme((Prefix + "Add.png")), "Add Image");
    QObject::connect(AddImage, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::ChangeImage);
    addAction(AddImage);

    QAction* RemoveImage = new QAction(QIcon::fromTheme((Prefix + "Subtract.png")), "Remove Image");
    QObject::connect(RemoveImage, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::RemoveImage);
    addAction(RemoveImage);

    addSeparator();

    QAction* ZoomIn = new QAction(QIcon::fromTheme((Prefix + "ZoomIn.png")), "Zoom In");
    QObject::connect(ZoomIn, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::ZoomIn);
    addAction(ZoomIn);

    QAction* ZoomOut = new QAction(QIcon::fromTheme((Prefix + "ZoomOut.png")), "Zoom Out");
    QObject::connect(ZoomOut, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::ZoomOut);
    addAction(ZoomOut);

    addSeparator();

    QAction* RotateLeft = new QAction(QIcon::fromTheme((Prefix + "RotateLeft.png")), "Rotate Left");
    QObject::connect(RotateLeft, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::RotateLeft);
    addAction(RotateLeft);

    QAction* RotateRight = new QAction(QIcon::fromTheme((Prefix + "RotateRight.png")), "Rotate Right");
    QObject::connect(RotateRight, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::RotateRight);
    addAction(RotateRight);

    addSeparator();

    QAction* BrightUp = new QAction(QIcon::fromTheme((Prefix + "BrightUp.png")), "Brightness Up");
    QObject::connect(BrightUp, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::BrightnessUp);
    addAction(BrightUp);

    QAction* BrightDown = new QAction(QIcon::fromTheme((Prefix + "BrightDown.png")), "Brightness Down");
    QObject::connect(BrightDown, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::BrightnessDown);
    addAction(BrightDown);

    addSeparator();

    QAction* ConstrastUp = new QAction(QIcon::fromTheme((Prefix + "ContrastUp.png")), "Contrast Up");
    QObject::connect(ConstrastUp, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::ContrastUp);
    addAction(ConstrastUp);

    QAction* ConstrastDown = new QAction(QIcon::fromTheme((Prefix + "ContrastDown.png")), "Contrast Down");
    QObject::connect(ConstrastDown, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::ContrastDown);
    addAction(ConstrastDown);

    setOrientation(Qt::Vertical);
}

PixeonCustomView* PixeonToolbar::GetParentAsCustomView() const
{
    return qobject_cast<PixeonCustomView*>(parent());
}

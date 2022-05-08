#include "pixeontoolbar.h"
#include "pixeoncustomview.h"
#include "mainwindow.h"

PixeonToolbar::PixeonToolbar(const QString& title, QWidget* parent)
    : QToolBar(title, parent)
{
    // This toolbar is intended to be used inside a Custom View widget, ensure that you pass a valid PixeonCustomView as parent
    assert(GetParentAsCustomView() != nullptr);

    const QString Prefix = ":/Pixeon/Assets/";

#define ADD_NEW_ACTION(PropertyName, ImageName, TooltipStr, Function) \
    QAction* PropertyName = new QAction(QIcon::fromTheme((Prefix + ImageName)), TooltipStr); \
    QObject::connect(PropertyName, &QAction::triggered, GetParentAsCustomView(), &PixeonCustomView::Function); \
    addAction(PropertyName)

    ADD_NEW_ACTION(AddImage, "Add.png", "Add Image", ChangeImage);
    ADD_NEW_ACTION(RemoveImage, "Subtract.png", "Remove Image", RemoveImage);

    addSeparator();

    ADD_NEW_ACTION(ZoomIn, "ZoomIn.png", "Zoom In", ZoomIn);
    ADD_NEW_ACTION(ZoomOut, "ZoomOut.png", "Zoom Out", ZoomOut);

    addSeparator();

    ADD_NEW_ACTION(RotateLeft, "RotateLeft.png", "Rotate Left", RotateLeft);
    ADD_NEW_ACTION(RotateRight, "RotateRight.png", "Rotate Right", RotateRight);

    addSeparator();

    ADD_NEW_ACTION(BrightUp, "BrightUp.png", "Brightness Up", BrightnessUp);
    ADD_NEW_ACTION(BrightDown, "BrightDown.png", "Brightness Down", BrightnessDown);

    addSeparator();

    ADD_NEW_ACTION(ContrastUp, "ContrastUp.png", "Contrast Up", ContrastUp);
    ADD_NEW_ACTION(ContrastDown, "ContrastDown.png", "Contrast Down", ContrastDown);

#undef ADD_NEW_ACTION

    setOrientation(Qt::Vertical);
}

PixeonCustomView* PixeonToolbar::GetParentAsCustomView() const
{
    return qobject_cast<PixeonCustomView*>(parent());
}

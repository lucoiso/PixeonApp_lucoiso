#include "pixeontoolbar.h"
#include "pixeoncustomview.h"
#include "mainwindow.h"

PixeonToolbar::PixeonToolbar(const QString &title, QWidget *parent)
    : QToolBar(title, parent)
{
    const QString Prefix = ":/Pixeon/Assets/";

    QAction* AddImage = new QAction(QIcon::fromTheme((Prefix + "Add.png")), "Add Image");
    QObject::connect(AddImage, &QAction::triggered, GetParentAsCustomView(), &CustomView::ChangeImage);
    addAction(AddImage);    

    QAction* RemoveImage = new QAction(QIcon::fromTheme((Prefix + "Subtract.png")), "Remove Image");
    QObject::connect(RemoveImage, &QAction::triggered, GetParentAsCustomView(), &CustomView::RemoveImage);
    addAction(RemoveImage);

    addSeparator();    

    QAction* ZoomIn = new QAction(QIcon::fromTheme((Prefix + "ZoomIn.png")), "Zoom In");
    QObject::connect(ZoomIn, &QAction::triggered, GetParentAsCustomView(), &CustomView::ZoomIn);
    addAction(ZoomIn);

    QAction* ZoomOut = new QAction(QIcon::fromTheme((Prefix + "ZoomOut.png")), "Zoom Out");
    QObject::connect(ZoomOut, &QAction::triggered, GetParentAsCustomView(), &CustomView::ZoomOut);
    addAction(ZoomOut);

    setOrientation(Qt::Vertical);
}

CustomView* PixeonToolbar::GetParentAsCustomView() const
{
    return qobject_cast<CustomView*>(parent());
}

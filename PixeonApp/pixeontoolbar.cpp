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
    addAction(new QAction(QIcon::fromTheme((Prefix + "ZoomIn.png")), "Zoom In"));
    addAction(new QAction(QIcon::fromTheme((Prefix + "ZoomOut.png")), "Zoom Out"));

    setOrientation(Qt::Vertical);
}

CustomView* PixeonToolbar::GetParentAsCustomView() const
{
    return qobject_cast<CustomView*>(parent());
}

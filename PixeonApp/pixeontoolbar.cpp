#include "pixeontoolbar.h"
#include "mainwindow.h"

PixeonToolbar::PixeonToolbar(const QString &title, QWidget *parent)
    : QToolBar(title, parent)
{
    const QString Prefix = ":/Pixeon/Assets/";

    QAction* AddImage = new QAction(QIcon::fromTheme((Prefix + "Add.png")), "Add Image");
    QObject::connect(AddImage, &QAction::triggered, GetParentAsWindow(), &MainWindow::AddNewImage);

    addAction(AddImage);
    addAction(new QAction(QIcon::fromTheme((Prefix + "Subtract.png")), "Remove Image"));
    addSeparator();
    addAction(new QAction(QIcon::fromTheme((Prefix + "ZoomIn.png")), "Zoom In"));
    addAction(new QAction(QIcon::fromTheme((Prefix + "ZoomOut.png")), "Zoom Out"));
}

MainWindow* PixeonToolbar::GetParentAsWindow() const
{
    return qobject_cast<MainWindow*>(parent());
}

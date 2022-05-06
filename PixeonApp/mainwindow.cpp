#include "mainwindow.h"
#include "pixeontoolbar.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addToolBar(Qt::ToolBarArea::LeftToolBarArea, new PixeonToolbar("Custom PixeonToolbar", this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddNewImage()
{
    // TO DO
    const QString PicturesFolder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    /*const QString FileName = */QFileDialog::getOpenFileName(this, QString(), PicturesFolder, "Image File (*.bmp *.png *.jpeg)");
}

void MainWindow::RemoveSelectedImage()
{
    // TO DO
}

QBitmap* MainWindow::GetSelectedImage()
{
    // TO DO
    return nullptr;
}

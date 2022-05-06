#include "mainwindow.h"
#include "pixeontoolbar.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QGraphicsView>

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
    // Work in Progress

    const QString PicturesFolder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    const QString FileName = QFileDialog::getOpenFileName(this, QString(), PicturesFolder, "Image File (*.bmp *.png *.jpeg)");

    if (FileName.count() != 0)
    {
        QPixmap NewImage(FileName);
        QGraphicsScene* NewScene = new QGraphicsScene(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
        NewScene->addPixmap(NewImage.scaled(QSize(ui->graphicsView->width(), ui->graphicsView->height())));
        ui->graphicsView->setScene(NewScene);
    }
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

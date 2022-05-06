#include "mainwindow.h"
#include "pixeontoolbar.h"
#include "ui_mainwindow.h"

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

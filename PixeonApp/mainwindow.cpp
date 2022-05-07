#include "mainwindow.h"
#include "pixeoncustomview.h"
#include "HelperFunctions.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    ui->tabWidget->clear();
    ui->tabWidget->addTab(new CustomView(this, ui->tabWidget), "Empty");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AddImage_triggered()
{
    ui->tabWidget->addTab(new CustomView(this, ui->tabWidget), "Empty");
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}


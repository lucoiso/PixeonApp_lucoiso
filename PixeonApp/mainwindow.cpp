#include "mainwindow.h"
#include "pixeoncustomview.h"
#include "pixeontoolbar.h"

#include "qlayout.h"
#include "ui_mainwindow.h"
#include "HelperFunctions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    const auto LayoutCreator = [&] () -> QVBoxLayout*
        {
            CustomView* NewCustomView = new CustomView(this);
            QVBoxLayout* BoxLayout = new QVBoxLayout();
            BoxLayout->addWidget(NewCustomView);

            return BoxLayout;
        };

    ui->tab->setLayout(LayoutCreator());
    ui->tab_2->setLayout(LayoutCreator());

    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_AddImage_triggered()
{
    ui->tabWidget->addTab(new CustomView(this), QString::number(ui->tabWidget->count() + 1));
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (ui->tabWidget->count() > 2)
    {
        ui->tabWidget->removeTab(index);
    }
}


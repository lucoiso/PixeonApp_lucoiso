#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddNewImage();
    void RemoveSelectedImage();

    QBitmap* GetSelectedImage();

private:
    Ui::MainWindow *ui;
};

#pragma once

#include <QToolBar>

class MainWindow;

class PixeonToolbar : public QToolBar
{
    Q_OBJECT

public:
   explicit PixeonToolbar(const QString &title, QWidget *parent = nullptr);

private:
    MainWindow* GetParentAsWindow() const;
};

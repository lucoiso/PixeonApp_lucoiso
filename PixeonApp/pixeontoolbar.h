#pragma once

#include <QToolBar>

class CustomView;

class PixeonToolbar : public QToolBar
{
    Q_OBJECT

public:
   explicit PixeonToolbar(const QString &title, QWidget *parent = nullptr);

private:
    CustomView* GetParentAsCustomView() const;
};

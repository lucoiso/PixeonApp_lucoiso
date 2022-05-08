#pragma once

#include <QToolBar>

class PixeonCustomView;

class PixeonToolbar : public QToolBar
{
    Q_OBJECT

public:
   explicit PixeonToolbar(const QString& title, QWidget* parent = nullptr);

protected:
    PixeonCustomView* GetParentAsCustomView() const;
};

#pragma once

#include <QToolBar>

class PixeonCustomView;

class PixeonToolbar : public QToolBar
{
    Q_OBJECT

public:
   explicit PixeonToolbar(const QString& title, QWidget* parent = nullptr);

protected:
    /* Helper function to get the parent casted as PixeonCustomView */
    PixeonCustomView* GetParentAsCustomView() const;
};

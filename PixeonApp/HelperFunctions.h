#pragma once

#include <QWidget>
#include <QString>
#include <QStandardPaths>
#include <QFileDialog>

namespace Helpers
{
    static const QString LoadNewImageFile(QWidget* Parent = nullptr)
    {
        const QString PicturesFolder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        return QFileDialog::getOpenFileName(Parent, QString(), PicturesFolder, "Image File (*.bmp *.png *.jpeg)");
    }
}

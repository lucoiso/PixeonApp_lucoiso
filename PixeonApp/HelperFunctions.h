#pragma once

#include <QWidget>
#include <QString>
#include <QStandardPaths>
#include <QFileDialog>

namespace Helpers
{
    /* Load a new image file using QFileDialog - return: File path as QString */
    static const QString LoadNewImageFile(QWidget* Parent = nullptr)
    {
        const QString PicturesFolder = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        return QFileDialog::getOpenFileName(Parent, QString(), PicturesFolder, "Image File (*.bmp *.png *.jpeg)");
    }
}

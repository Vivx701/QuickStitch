#include "imagestitcher.h"
#include <QDebug>
ImageList ImageStitcher::getImageList() const
{
    return imageList;
}

ImageStitcher::ImageStitcher(QObject *parent) : QObject(parent)
{

}

void ImageStitcher::addImages(ImageList imgList)
{
    imageList.append(imgList);
}

void ImageStitcher::addImage(QImage image)
{
    imageList.append(image);
}

void ImageStitcher::addImage(QString location)
{
    QImage img;
    img.load(location);
    imageList.append(img);
}


QImage ImageStitcher::horizontalStitch(QColor bgColor)
{
    int imgwidth = 0;
    int imgheight = 0;

    for(QImage img: imageList){

        imgheight = img.height() > imgheight ? img.height(): imgheight;
        imgwidth += img.width();
    }

    qDebug()<<imgwidth<< imgheight;
    emit finalImageSizeChanged(QSize(imgwidth, imgheight));
    QImage finalImage(imgwidth, imgheight, QImage::Format_ARGB32);
    finalImage.fill(bgColor);
    int drawingIndex = 0;
    emit progressChanged(imageList.count(), 0);
    for(int i= 0; i<imageList.count(); i++){
        QImage img = imageList.at(i);

        for(int i=0;i<img.height(); i++){

            for(int j=0; j<img.width(); j++){

                QRgb color = img.pixel(j, i);
                finalImage.setPixel(drawingIndex+j, i, color);
            }
        }
        drawingIndex += img.width();
        emit progressChanged(imageList.count(), i+1);
    }

    return finalImage;
}

QImage ImageStitcher::verticalStitch(QColor bgColor)
{
    int imgwidth = 0;
    int imgheight = 0;

    for(QImage img: imageList){

        imgwidth = img.width() > imgwidth ? img.width(): imgwidth;
        imgheight += img.height();
    }


    emit finalImageSizeChanged(QSize(imgwidth, imgheight));
    QImage finalImage(imgwidth, imgheight, QImage::Format_ARGB32);
    finalImage.fill(bgColor);
    int drawingIndex = 0;
    emit progressChanged(imageList.count(), 0);
    for(int i= 0; i<imageList.count(); i++){
        QImage img = imageList.at(i);

        for(int i=0;i<img.height(); i++){

            for(int j=0; j<img.width(); j++){

                QRgb color = img.pixel(j, i);
                finalImage.setPixel(j, drawingIndex+i, color);
            }
        }
        drawingIndex += img.height();
        emit progressChanged(imageList.count(), i+1);
    }

    return finalImage;
}

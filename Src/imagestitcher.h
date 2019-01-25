#ifndef IMAGESTITCHER_H
#define IMAGESTITCHER_H

#include <QObject>
#include <QImage>
#include <QList>
#include <QColor>
enum StitchType{ HORIZONTAL, VERTICAL};
typedef QList<QImage> ImageList;
class ImageStitcher : public QObject
{
    Q_OBJECT


private:

    ImageList imageList;
public:
    explicit ImageStitcher(QObject *parent = nullptr);
    void addImages(ImageList imgList);
    void addImage(QImage image);
    void addImage(QString location);
    QImage horizontalStitch(QColor bgColor=Qt::white);
    QImage verticalStitch(QColor bgColor=Qt::white);

    ImageList getImageList() const;

signals:
    void progressChanged(int maximum, int value);
    void finalImageSizeChanged(QSize size);
public slots:
};

#endif // IMAGESTITCHER_H

#ifndef STITCHDIALOG_H
#define STITCHDIALOG_H

#include <QDialog>
#include <QColor>
#include <QSize>
#include "imagestitcher.h"

namespace Ui {
class StitchDialog;
}

class StitchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StitchDialog(QWidget *parent = 0);
    void addImages(ImageList imgList);
    void addImage(QImage img);
    ~StitchDialog();

private slots:
    void onBgColorValueTextChanged(const QString color);
    void onChooseColor();
    void onChooseFileName();
    void onTypeSelected(QString type);
    void updateDetails();
    void onProgressChange(int maximum, int value);
    void onFinalImageSizeChanged(QSize size);
    void onStartButtonClicked();

private:
    Ui::StitchDialog *ui;
    QColor bgColor;
    QString saveFileName;
    QString selectedType;
    QSize finalImageSize;
    ImageStitcher *m_stitcher;
};

#endif // STITCHDIALOG_H

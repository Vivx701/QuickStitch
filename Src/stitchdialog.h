#ifndef STITCHDIALOG_H
#define STITCHDIALOG_H

#include <QDialog>
#include <QColor>

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
    ~StitchDialog();

    void setBgColor(const QColor &value);
    void setStitchType(StitchType type);

private slots:
    void onSaveButtonClicked();
    void onBrowseButtonClicked();
    void onProgresChanged(int maximum, int value);


private:
    Ui::StitchDialog *ui;
    ImageStitcher *stitcher;
    QColor bgColor;
    StitchType sType;

};

#endif // STITCHDIALOG_H

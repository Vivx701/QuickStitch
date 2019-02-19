#ifndef STITCHDIALOG_H
#define STITCHDIALOG_H

#include <QDialog>
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

private:
    Ui::StitchDialog *ui;
    ImageStitcher *stitcher;
};

#endif // STITCHDIALOG_H

#include "stitchdialog.h"
#include "ui_stitchdialog.h"

StitchDialog::StitchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StitchDialog)
{
    ui->setupUi(this);
    stitcher = new ImageStitcher(this);
}

void StitchDialog::addImages(ImageList imgList)
{
    stitcher->addImages(imgList);
}

StitchDialog::~StitchDialog()
{
    delete ui;
}

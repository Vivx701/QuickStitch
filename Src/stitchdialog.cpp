#include "stitchdialog.h"
#include "ui_stitchdialog.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QImageWriter>

StitchDialog::StitchDialog(QWidget *parent) :
    QDialog(parent), sType(HORIZONTAL),
    ui(new Ui::StitchDialog)
{
    ui->setupUi(this);
    stitcher = new ImageStitcher(this);
    connect(ui->browseButton, SIGNAL(clicked(bool)), SLOT(onBrowseButtonClicked()));
    connect(ui->saveButton, SIGNAL(clicked(bool)), SLOT(onSaveButtonClicked()));
    connect(stitcher, SIGNAL(progressChanged(int,int)), SLOT(onProgresChanged(int,int)));

}

void StitchDialog::addImages(ImageList imgList)
{
    stitcher->addImages(imgList);
}

StitchDialog::~StitchDialog()
{
    delete ui;
}

void StitchDialog::onSaveButtonClicked()
{
    QString savePath = QDir::cleanPath(ui->savePathlineEdit->text());
    if(savePath.isEmpty()){

        QMessageBox::about(this, "failed to save",  "Empty file name to save");
        return;
    }

    QImage img;
    switch (sType) {
    case HORIZONTAL:
        img = stitcher->horizontalStitch(bgColor);
        break;
    case VERTICAL:
        img = stitcher->verticalStitch(bgColor);
        break;
    default:
        break;
    }

    QImageWriter imageWriter(savePath);
    if(imageWriter.write(img)){
        QMessageBox::about(this, "finish",  " image saved "+savePath);
    }else{
        QMessageBox::about(this, "finish",  imageWriter.errorString());
    }
}

void StitchDialog::onBrowseButtonClicked()
{

    QString dir = QDir::cleanPath(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + QDir::separator() + "image");
    QString *selectedFilter = new QString();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), dir,
                               tr("JPG(*.jpg);;PNG(*.png);;BMP(*.bmp)"), selectedFilter);

    bool validFormat = true;
    IMAGEFORMAT selectedFormat;
    if(selectedFilter->toLatin1() == "JPG(*.jpg)"){
        selectedFormat = IMAGEFORMAT::JPG;
    }else if(selectedFilter->toLatin1() == "PNG(*.png)"){
        selectedFormat = IMAGEFORMAT::PNG;
    }else if(selectedFilter->toLatin1() == "BMP(*.bmp)"){
        selectedFormat = IMAGEFORMAT::BMP;
    }else{
        validFormat = false;
    }

    if(!validFormat){

        QMessageBox::about(this, "Not a valid format", "Please select avalid format");
    }
    ui->savePathlineEdit->setText(fileName);
}

void StitchDialog::onProgresChanged(int maximum, int value)
{
    ui->stitchProgressBar->setMaximum(maximum);
    ui->stitchProgressBar->setValue(value);
}

void StitchDialog::setBgColor(const QColor &value)
{
    bgColor = value;
}

void StitchDialog::setStitchType(StitchType type)
{
    sType = type;
}

#include <QColorDialog>
#include <QPalette>
#include <QFileDialog>
#include <QImageWriter>
#include <QMessageBox>
#include "stitchdialog.h"
#include "ui_stitchdialog.h"

StitchDialog::StitchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StitchDialog), bgColor("#FBFBFC"), finalImageSize(0, 0)
{
    ui->setupUi(this);

    connect(ui->chooseColorButton, SIGNAL(clicked(bool)), this, SLOT(onChooseColor()));
    connect(ui->filenameChoose, SIGNAL(clicked(bool)), this, SLOT(onChooseFileName()));
    connect(ui->typeSelection, SIGNAL(currentTextChanged(QString)), this, SLOT(onTypeSelected(QString)));
    connect(ui->startButton, SIGNAL(clicked(bool)) , this, SLOT(onStartButtonClicked()));
    ui->bgColorValue->setText(bgColor.name().toUpper());
    selectedType = ui->typeSelection->currentText();

    m_stitcher = new ImageStitcher(this);
    connect(m_stitcher, SIGNAL(progressChanged(int,int)), this, SLOT(onProgressChange(int,int)));
    connect(m_stitcher, SIGNAL(finalImageSizeChanged(QSize)), this, SLOT(onFinalImageSizeChanged(QSize)));
    connect(ui->bgColorValue, SIGNAL(textEdited(QString)), this, SLOT(onBgColorValueTextChanged(QString)));
    updateDetails();
}

void StitchDialog::addImages(ImageList imgList)
{
    m_stitcher->addImages(imgList);

}

void StitchDialog::addImage(QImage img)
{
    m_stitcher->addImage(img);
}


StitchDialog::~StitchDialog()
{
    m_stitcher->deleteLater();
    delete ui;
}

void StitchDialog::onBgColorValueTextChanged(const QString color)
{
    ui->bgColorValue->setText(color.toUpper());
    ui->colorViewer->setAutoFillBackground(true);
    QPalette bgColorPalette = ui->colorViewer->palette();
    bgColor = QColor(color);
    bgColorPalette.setColor(QPalette::Background, bgColor);
    ui->colorViewer->setPalette(bgColorPalette);
    updateDetails();

}

void StitchDialog::onChooseColor()
{
    QColor selectedColor = QColorDialog::getColor(bgColor, this, "Choose Color");
    if(selectedColor.isValid()){
        bgColor = selectedColor;
        ui->bgColorValue->setText(bgColor.name());
    }

}

void StitchDialog::onChooseFileName()
{
    QString fileName =  QFileDialog::getSaveFileName(this, "Save Image", "stich","jpg (*.jpg);;png(*.png);;");
    if(fileName.isEmpty()){
        return;
    }
    saveFileName = fileName;
    ui->selectedPath->setText(saveFileName);
    updateDetails();
}

void StitchDialog::onTypeSelected(QString type)
{
     selectedType = type;
     updateDetails();
}

void StitchDialog::updateDetails()
{

    QString details = "Path: %1\n\n\n"
                      "Background: %2\n"
                      "Type: %3\n"
                      "Size: %4\n"
                       "Count: %5";
    QString size = QString::number(finalImageSize.width())+" X "+QString::number(finalImageSize.height());
    ui->outputLabel->setText(details.arg(saveFileName).arg(bgColor.name().toUpper()).arg(selectedType).arg(size).arg(QString::number(m_stitcher->getImageList().length())));

}



void StitchDialog::onProgressChange(int maximum, int value)
{

    ui->stitchProgressBar->setMaximum(maximum);
    ui->stitchProgressBar->setValue(value);
}

void StitchDialog::onFinalImageSizeChanged(QSize size)
{

    finalImageSize = size;
    updateDetails();
}



void StitchDialog::onStartButtonClicked()
{


    if(saveFileName.isEmpty()){
       QMessageBox::information(this, "File name is empty", "Please select a location and name to save the image.<br/>"
                                                            "Press File button to choose file path.", QMessageBox::Ok);
       return;
    }
    QImage img;
    if(selectedType == "Horizontal"){
       img = m_stitcher->horizontalStitch(bgColor);
    }else if(selectedType == "Vertical"){
        img = m_stitcher->verticalStitch(bgColor);
    }


    QImageWriter   imageWriter( saveFileName );
    if(imageWriter.write(img)){
        QMessageBox::about(this, "finish",  " image saved "+ saveFileName);
    }else{
        QMessageBox::about(this, "finish",  imageWriter.errorString());
    }

}

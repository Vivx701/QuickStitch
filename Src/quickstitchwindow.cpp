#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QList>
#include <QDateTime>
#include <QPixmap>
#include <QImageWriter>
#include "quickstitchwindow.h"
#include "ui_quickstitchwindow.h"
#include "stitchdialog.h"

QuickStitchWindow::QuickStitchWindow(QWidget *parent) :
    QMainWindow(parent),bgColor("#FBFBFC"),
    ui(new Ui::QuickStitchWindow)
{
    ui->setupUi(this);
    ui->imageListWidget->setIconSize(QSize(100, 100));
    connect(ui->actionAddImages, SIGNAL(triggered(bool)), this, SLOT(onAddImageButtonClicked()));
    connect(ui->actionRemoveImages, SIGNAL(triggered(bool)), this,SLOT(onRemoveImageButtonClicked()));
    connect(ui->actionMoveUp, SIGNAL(triggered(bool)), this,SLOT(onMoveUpButtonClicked()));
    connect(ui->actionMoveDown, SIGNAL(triggered(bool)), this,SLOT(onMoveDownButtonClicked()));
    connect(ui->hStitchButton, SIGNAL(clicked(bool)), this, SLOT(onHStitchButtonClicked()));
    connect(ui->vStitchButton, SIGNAL(clicked(bool)), this, SLOT(onVStitchButtonClicked()));
    connect(ui->actionBackground_color, SIGNAL(triggered(bool)), this, SLOT(onChooseColor()));
    connect(this, SIGNAL(showError(QString,QString)), this, SLOT(showErrorMessage(QString,QString)));

}

ImageList QuickStitchWindow::getImageList()
{
    ImageList imgList;
    for(int i=0; i<ui->imageListWidget->count(); i++ ){

        QListWidgetItem *item = ui->imageListWidget->item(i);
        QString filePath = item->data(Qt::UserRole).toString();

        if(!QFileInfo(filePath).exists()){
            emit showError("Failed to load image", "Failed to load image from path "+filePath);
            continue;
        }

        QImage img(filePath);
        if(!img.isNull()){
          imgList.append(img);
        }else{
           emit showError("Failed to load image", "Seems like an invalid image"+filePath);
        }
    }
    return imgList;
}

QuickStitchWindow::~QuickStitchWindow()
{
    delete ui;
}

void QuickStitchWindow::onAddImageButtonClicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"),"", "Images (*.png *.jpg *.bmp *.jpeg)");

    for(QString file: files){

        QFileInfo info(file);
        if(!info.exists()){

            showError("File not found", file+" file not found");
            continue;
        }
        QPixmap pixImg(file);
        QString fileDetails = QString(" %1     (%2X%3)").arg(info.fileName()).arg(pixImg.size().width()).arg(pixImg.size().height());
        QListWidgetItem *item = new QListWidgetItem(QIcon(pixImg), fileDetails, ui->imageListWidget);
        item->setData(Qt::UserRole, info.filePath());
        ui->imageListWidget->addItem(item);
    }
}



void QuickStitchWindow::onRemoveImageButtonClicked()
{
    qDeleteAll(ui->imageListWidget->selectedItems());
}

void QuickStitchWindow::onMoveUpButtonClicked()
{
    QList<QListWidgetItem *> selectedList = ui->imageListWidget->selectedItems();

    for(int i=0; i<selectedList.count(); i++ ){

        int currentIndex = ui->imageListWidget->row(selectedList.at(i));
        if(currentIndex == 0){
            continue;
        }

        int moveTo = currentIndex-1;
        QListWidgetItem *temp = ui->imageListWidget->takeItem(currentIndex);
        ui->imageListWidget->insertItem(moveTo, temp);
        ui->imageListWidget->setCurrentItem(temp);

    }
}

void QuickStitchWindow::onMoveDownButtonClicked()
{
    QList<QListWidgetItem *> selectedList = ui->imageListWidget->selectedItems();

    for(int i=0; i<selectedList.count(); i++ ){

        int currentIndex = ui->imageListWidget->row(selectedList.at(i));
        if(currentIndex == ui->imageListWidget->count()-1){
            continue;
        }

        int moveTo = currentIndex+1;
        QListWidgetItem *temp = ui->imageListWidget->takeItem(currentIndex);
        ui->imageListWidget->insertItem(moveTo, temp);
        ui->imageListWidget->setCurrentItem(temp);

    }
}


void QuickStitchWindow::onHStitchButtonClicked()
{
    if(ui->imageListWidget->count()<1){

        QMessageBox::information(this, "No Images ", "Select the images you need to stitch.<br/>"                                            "Press AddImages button to choose images", QMessageBox::Ok);
        return;
    }
    ImageList imgList = getImageList();
    startStich(imgList, HORIZONTAL);

}

void QuickStitchWindow::onVStitchButtonClicked()
{
    if(ui->imageListWidget->count()<1){
        QMessageBox::information(this, "No Images ", "Select the images you need to stitch.<br/>"
                                                          "Press AddImages button to choose images", QMessageBox::Ok);
        return;
    }
    ImageList imgList = getImageList();
    startStich(imgList, VERTICAL);
}

void QuickStitchWindow::onChooseColor()
{
    QColor selectedColor = QColorDialog::getColor(bgColor, this, "Choose Color");
    if(selectedColor.isValid()){
        bgColor = selectedColor;
    }

}

void QuickStitchWindow::startStich(ImageList imgList, StitchType type)
{

    StitchDialog stitchDialog;
    stitchDialog.setFixedSize(574, 128);
    stitchDialog.addImages(imgList);
    stitchDialog.setBgColor(bgColor);
    stitchDialog.setStitchType(type);
    stitchDialog.exec();

}



void QuickStitchWindow::showErrorMessage(QString heading, QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setWindowTitle(heading);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();

}



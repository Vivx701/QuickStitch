#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QList>
#include <QDateTime>
#include <QPixmap>
#include "quickstitchwindow.h"
#include "ui_quickstitchwindow.h"
#include "stitchdialog.h"
QuickStitchWindow::QuickStitchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuickStitchWindow)
{
    ui->setupUi(this);

    ui->imageListWidget->setIconSize(QSize(100, 100));
    connect(ui->actionAddImages, SIGNAL(triggered(bool)), this, SLOT(onAddImageButtonClicked()));
    connect(ui->actionRemoveImages, SIGNAL(triggered(bool)), this,SLOT(onRemoveImageButtonClicked()));
    connect(ui->actionMoveUp, SIGNAL(triggered(bool)), this,SLOT(onMoveUpButtonClicked()));
    connect(ui->actionMoveDown, SIGNAL(triggered(bool)), this,SLOT(onMoveDownButtonClicked()));
    connect(ui->stitchButton, SIGNAL(clicked(bool)), this, SLOT(openStitchDialog()));
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

void QuickStitchWindow::showError(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
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

void QuickStitchWindow::openStitchDialog()
{
    if(ui->imageListWidget->count()<1){

        QMessageBox::information(this, "No Images ", "Select the images you need to stitch.<br/>"
                                                             "Press AddImages button to choose images", QMessageBox::Ok);
        return;
    }

   StitchDialog Dialog;
   for(int i=0; i<ui->imageListWidget->count(); i++ ){

       QListWidgetItem *item = ui->imageListWidget->item(i);
       QString filePath = item->data(Qt::UserRole).toString();

       if(!QFileInfo(filePath).exists()){

           continue;
       }

       QImage img(filePath);
       if(!img.isNull()){
         Dialog.addImage(img);
       }

   }

   Dialog.exec();
}

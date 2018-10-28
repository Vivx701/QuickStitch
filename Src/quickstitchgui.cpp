#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QList>

#include "quickstitchgui.h"
#include "ui_quickstitchgui.h"
#include "stitchdialog.h"
QuickStitchGui::QuickStitchGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuickStitchGui)
{
    ui->setupUi(this);
    ui->imageListWidget->setIconSize(QSize(100, 100));


    connect(ui->addImageButton, SIGNAL(clicked(bool)), this, SLOT(onAddImageButtonClicked()));
    connect(ui->removeImageButton, SIGNAL(clicked(bool)), this,SLOT(onRemoveImageButtonClicked()));
    connect(ui->moveUpButton, SIGNAL(clicked(bool)), this,SLOT(onMoveUpButtonClicked()));
    connect(ui->moveDownButton, SIGNAL(clicked(bool)), this,SLOT(onMoveDownButtonClicked()));
    connect(ui->stitchButton, SIGNAL(clicked(bool)), this, SLOT(openStitchDialog()));

}

QuickStitchGui::~QuickStitchGui()
{
    delete ui;
}

void QuickStitchGui::onAddImageButtonClicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"),"", "Images (*.png *.jpg *.bmp *.jpeg)");

    for(QString file: files){

        QFileInfo info(file);
        if(!info.exists()){

            showError("File not found", file+" file not found");
            continue;
        }

        QListWidgetItem *item = new QListWidgetItem(QIcon(file), info.fileName(), ui->imageListWidget);
        item->setData(Qt::UserRole, info.filePath());
        ui->imageListWidget->addItem(item);
    }
}

void QuickStitchGui::showError(QString title, QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(message);
    msgBox.exec();
}

void QuickStitchGui::onRemoveImageButtonClicked()
{
    qDeleteAll(ui->imageListWidget->selectedItems());
}

void QuickStitchGui::onMoveUpButtonClicked()
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

void QuickStitchGui::onMoveDownButtonClicked()
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

void QuickStitchGui::openStitchDialog()
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

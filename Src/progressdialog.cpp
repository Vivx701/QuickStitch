#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::onProgressChanged(int maximum, int value)
{
    ui->progressBar->setMaximum(maximum);
    ui->progressBar->setValue(value);

    ui->progressLabel->setText(ui->progressBar->text());
    ui->progressMessageLabel->setText(QString("Stitching image in progress ..... (%/%)").arg(value).arg(maximum));


}

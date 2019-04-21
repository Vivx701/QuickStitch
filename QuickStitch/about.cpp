#include "about.h"
#include "ui_about.h"
#include "strings.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->detailsContainer->setText(aboutContent());
}

About::~About()
{
    delete ui;
}

void About::on_aboutQtButton_clicked()
{
    QMessageBox::aboutQt(this, APPLICATION_NAME);
}

QString About::aboutContent()
{
    QString content = QString("<center>"
                              " <h1>%1</h1>"
                              "Version: %2<br/>"
                              "License: GPL"
                              "<p>"
                              "Simple image stitching program to join images"
                              "</p><br/>"
                              "Author: %3 ( %4 )<br/>"
                              "</center>").arg(APPLICATION_NAME).arg(VERSION).arg(AUTHOR).arg(AUTHOR_GIT_PAGE).arg(PROJECT_HOME_PAGE);

    return content;
}

void About::on_homePageButton_clicked()
{
    QDesktopServices::openUrl(QUrl(PROJECT_HOME_PAGE));
}

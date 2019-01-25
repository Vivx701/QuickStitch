#include "quickstitchwindow.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheet(":/default.qss");
    if (!styleSheet.open(QIODevice::ReadOnly | QIODevice::Text)){

        QMessageBox::critical(nullptr, "Failed to open stylesheet", "Failed to open stylesheet:  "+ styleSheet.errorString());
    }else{

        a.setStyleSheet(QString::fromLocal8Bit(styleSheet.readAll()));
    }
    QuickStitchWindow window;
    window.show();

    return a.exec();
}

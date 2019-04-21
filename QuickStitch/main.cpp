#include "quickstitchwindow.h"
#include "strings.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APPLICATION_NAME);
    a.setApplicationVersion(VERSION);

    QFile styleSheet(":/default.qss");
    if (!styleSheet.open(QIODevice::ReadOnly | QIODevice::Text)){

        QMessageBox::critical(nullptr, "Failed to open stylesheet", "Failed to open stylesheet:  "+ styleSheet.errorString());
    }else{

        a.setStyleSheet(QString::fromLocal8Bit(styleSheet.readAll()));
    }
    QuickStitchWindow window;
    window.setWindowTitle(a.applicationName());
    window.setWindowIcon(QIcon(":/data/icons/QuickStitch.svg"));
    window.show();

    return a.exec();
}

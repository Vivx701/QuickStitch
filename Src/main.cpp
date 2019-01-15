#include "quickstitchwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuickStitchWindow w;
    w.show();

    return a.exec();
}

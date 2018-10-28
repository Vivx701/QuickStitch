#include "quickstitchgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuickStitchGui w;
    w.show();

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <verificationwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VerificationWidget w;
    w.show();

    return a.exec();
}

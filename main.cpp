#include <QCoreApplication>
#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Backend *temp = new Backend();
//    qDebug() << "start";
    return a.exec();
}

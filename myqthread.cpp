#include "myqthread.h"
#include "QDebug"
myQThread::myQThread(QObject *parent) : QThread(parent)
{

}

void myQThread::run()
{
    while (1)
    {
        sleep(1);
        //qDebug() << "myThread";
    }
}

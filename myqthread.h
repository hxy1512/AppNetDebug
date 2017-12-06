#ifndef MYQTHREAD_H
#define MYQTHREAD_H

#include <QObject>
#include <QThread>
class myQThread : public QThread
{
    Q_OBJECT
public:
    explicit myQThread(QObject *parent = nullptr);

signals:

public slots:
protected:
    void run();
};

#endif // MYQTHREAD_H

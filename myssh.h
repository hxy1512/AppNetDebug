#ifndef MYSSH_H
#define MYSSH_H

#include <QObject>
#include "include/QSsh"
class mySsh : public QObject
{
    Q_OBJECT
public:
    explicit mySsh(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYSSH_H

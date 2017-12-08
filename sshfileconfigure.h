#ifndef SSHFILECONFIGURE_H
#define SSHFILECONFIGURE_H

#include <QObject>

class sshFileConfigure : public QObject
{
    Q_OBJECT
public:
    explicit sshFileConfigure(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SSHFILECONFIGURE_H
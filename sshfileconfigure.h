#ifndef SSHFILECONFIGURE_H
#define SSHFILECONFIGURE_H

#include <QObject>
#include <QFile>
#include "myssh.h"

class sshFileConfigure : public QObject
{
    Q_OBJECT
public:
    explicit sshFileConfigure(QObject *parent = nullptr);
    void f_getSshUserConfigure();
    void f_setSshUserConfigure();
signals:
    void sgn_readUserConfigureOK(mySsh::sshInfo);
public slots:
private:
    QFile *m_file;
    mySsh::sshInfo *m_sshinfo;
};

#endif // SSHFILECONFIGURE_H

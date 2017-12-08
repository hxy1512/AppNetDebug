#ifndef MYSSH_H
#define MYSSH_H

#include <QObject>
#include "include/QSsh"
#include "QDebug"
class mySsh : public QObject
{
    Q_OBJECT
public:
    //hello
    typedef struct SSHINFO
    {
      QString userName;
      QString password;
      int port;
      int timeout;
      QString host;
      QSsh::SshConnectionParameters::AuthenticationType verifyType;
    }sshInfo;

public:
    explicit mySsh(QObject *parent = nullptr);
    void f_setSshInfo(mySsh::sshInfo info);
    void f_connectSshServer();

signals:

public slots:
    void slot_SshConnected();
    void slot_SshError(QSsh::SshError);
    void slot_SshDisconnected();
    void slot_SshDataAvailable(const QString &message);
    void slot_SshReadyRead();
    void slot_SshStarted();
    void slot_SshReadyReadStandarOutput();
    void slot_SshReadReadStandarError();
    void slot_SshMProcessClosed();

private:
    mySsh::sshInfo *m_sshInfo;
    QSsh::SshConnectionParameters m_params;
    QSsh::SshConnection *m_connection;
    QSharedPointer<QSsh::SshRemoteProcess> m_process;

};

#endif // MYSSH_H

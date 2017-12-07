#ifndef MYSSH_H
#define MYSSH_H

#include <QObject>
#include "include/QSsh"
class mySsh : public QObject
{
    Q_OBJECT
private:
    typedef struct m_sshInfo
    {
      QString userName;
      QString password;
      int port;
      int timeout;
      QString host;
      QSsh::SshConnectionParameters::AuthenticationType m_type;


    }m_sshInfo;
public:
    explicit mySsh(QObject *parent = nullptr);
    void f_setSshInfo(m_sshInfo);

signals:

public slots:

private:
    QSsh::SshConnectionParameters *m_params;
    QSsh::SshConnection *m_connection;
    QSharedPointer<QSsh::SshRemoteProcess> *m_process;

    /*
     *
     *     m_params.userName = ui->m_line_username->text();
    m_params.password = ui->m_line_pwd->text();
    m_params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    m_params.port = ui->m_line_port->text().toInt();
    m_params.timeout = 10;
    m_params.host = ui->m_line_ip->text();
    */
};

#endif // MYSSH_H

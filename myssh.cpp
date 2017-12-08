#include "myssh.h"

mySsh::mySsh(QObject *parent) : QObject(parent)
{
    //m_params = new QSsh::SshConnectionParameters;
    connectStatus = false;

}

void mySsh::f_setSshInfo(mySsh::sshInfo info)
{
    m_sshInfo = new mySsh::sshInfo;
    m_sshInfo = &info;
    //qDebug() << m_sshInfo->host << m_sshInfo->password << m_sshInfo->userName << "xyfish~";
    m_params.host = info.host;
    m_params.password = info.password;
    m_params.port = info.port;
    m_params.timeout = info.timeout;
    m_params.userName = info.userName;
    m_params.authenticationType = info.verifyType;
}

void mySsh::f_connectSshServer()
{
    m_connection = new QSsh::SshConnection(m_params);
    connect(m_connection, SIGNAL(connected()), this, SLOT(slot_SshConnected()));
    connect(m_connection, SIGNAL(error(QSsh::SshError)), this, SLOT(slot_SshError(QSsh::SshError)));
    connect(m_connection, SIGNAL(disconnected()), this, SLOT(slot_SshDisconnected()));
    connect(m_connection, SIGNAL(dataAvailable(QString)), this, SLOT(slot_SshDataAvailable(QString)));
    m_connection->connectToHost();


    //connect(mySsh::m_process.data(), SIGNAL(readyRead()), this, SLOT(slot_SshReadyRead()));
//    connect(m_process.data(), SIGNAL(started()), this, SLOT(slot_SshStarted()));
//    connect(m_process.data(), SIGNAL(readyReadStandardOutput()),this, SLOT(slot_SshReadyReadStandarOutput()));
//    connect(m_process.data(), SIGNAL(readyReadStandardError()), this, SLOT(slot_SshReadReadStandarError()));
//    connect(m_process.data(), SIGNAL(closed(int)), this, SLOT(slot_SshMProcessClosed()));

//    m_process.data()->start();

}

void mySsh::f_sendSshMessage(QString str)
{
    if(mySsh::f_isConnected())
        m_process.data()->write(str.toLatin1());
}

bool mySsh::f_isConnected()
{
    if(connectStatus)
        return true;
    else
        return false;
}

//mySsh::sshInfo mySsh::operator=(mySsh::sshInfo &info2)
//{
//    mySsh::sshInfo info_rtn;
//    info_rtn.host = info2.host;
//    info_rtn.password = info2.password;
//    info_rtn.port = info2.port;
//    info_rtn.timeout = info2.timeout;
//    info_rtn.userName = info2.userName;
//    info_rtn.verifyType = info2.verifyType;
//    return info_rtn;
//}

void mySsh::slot_SshConnected()
{
    qDebug() << "xyfish: connected";
    m_process = m_connection->createRemoteShell();
    connect(mySsh::m_process.data(), SIGNAL(readyRead()), this, SLOT(slot_SshReadyRead()));
    connect(m_process.data(), SIGNAL(started()), this, SLOT(slot_SshStarted()));
    connect(m_process.data(), SIGNAL(readyReadStandardOutput()),this, SLOT(slot_SshReadyReadStandarOutput()));
    connect(m_process.data(), SIGNAL(readyReadStandardError()), this, SLOT(slot_SshReadReadStandarError()));
    connect(m_process.data(), SIGNAL(closed(int)), this, SLOT(slot_SshMProcessClosed()));

    m_process.data()->start();

}

void mySsh::slot_SshError(QSsh::SshError)
{
    qDebug() << "xyfish: ssherror";
}

void mySsh::slot_SshDisconnected()
{
    qDebug() << "xyfish: Disconnected";
}

void mySsh::slot_SshDataAvailable(const QString &message)
{
    qDebug() << "xyfish: sshdataaviliable";
}

void mySsh::slot_SshReadyRead()
{
    qDebug() << "xyfish: readread";
}

void mySsh::slot_SshStarted()
{
    qDebug() << "xyfish: sshstarted";
    connectStatus = true;
}

void mySsh::slot_SshReadyReadStandarOutput()
{
    qDebug() << "xyfish: readreadstandaroutput";
    QString str = m_process.data()->readAllStandardOutput().data();
    //qDebug() << str;
    emit sgn_msgShowUI(str);

}

void mySsh::slot_SshReadReadStandarError()
{
    qDebug() << "xyfish: readreadstandarerror";
}

void mySsh::slot_SshMProcessClosed()
{
    qDebug() << "xyfish: mprocessclosed";
}

#include "sshfileconfigure.h"

sshFileConfigure::sshFileConfigure(QObject *parent) : QObject(parent)
{
    m_file = new QFile("sshConfigure.txt");
    m_sshinfo = new mySsh::sshInfo;
}

void sshFileConfigure::f_getSshUserConfigure()
{
    m_file->open(QIODevice::ReadWrite);
    for(int i = 0; !m_file->atEnd(); i++)
    {
        QString str = m_file->readLine();
        str.replace("\n", "");
        switch (i) {
        case 0://ip
            m_sshinfo->host = str;
            break;
        case 1: //user
            //ui->m_line_username->setText(str);
            m_sshinfo->userName = str;
            break;
        case 2: //pwd
            //ui->m_line_pwd->setText(str);
            m_sshinfo->password = str;
            break;
        case 3: //port
//            ui->m_line_port->setText(str);
            m_sshinfo->port = str.toInt();
            break;
        default:
            break;
        }
    }
    m_sshinfo->timeout = 10;
    m_sshinfo->verifyType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    qDebug() << m_sshinfo->host << m_sshinfo->password << m_sshinfo->userName << "xyfish!";
    emit sgn_readUserConfigureOK(*m_sshinfo);
}

void sshFileConfigure::f_setSshUserConfigure()
{

}

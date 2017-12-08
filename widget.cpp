#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
#include "QThread"
#include "myqthread.h"
#include "QTextCursor"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_ssh = new mySsh;
    ui->m_line_ip->setText("127.0.0.1");
    ui->m_line_port->setText("22");
    ui->m_line_pwd->setText("zxcasd");
    ui->m_line_username->setText("xyfish");
    ui->m_btn_connect->setText("connect");
    ui->m_btn_quit->setText("exit");
    connect(ui->m_line_inputcmd, SIGNAL(returnPressed()), this, SLOT(slot_InputCmdLineReturnPressed()));
    connect(m_ssh, SIGNAL(sgn_msgShowUI(QString)), this, SLOT(slot_SshMessageShowUi(QString)));
    f_OpenSshConfig();
   // m_thread = new myQThread(this);
}

void Widget::f_OpenSshConfig()
{
    m_file = new QFile("sshConfigure.txt");
    m_file->open(QIODevice::ReadWrite);
    while (!m_file->atEnd())
    {
        QString str= m_file->readLine();
        str.replace("\n", "");
        //ui->m_text_Ssh_Status->append(QString::number(str.length()));
        ui->m_text_Ssh_Status->append(str);
    }
}

Widget::~Widget()
{
    delete ui;
    delete m_thread;
    //delete m_connection;
}
/*********When Ssh Started Will Call This Func*************/
//void Widget::slot_SshStarted()
//{
//    ui->m_text_Ssh_Status->append("get started");
//}
/***********When SshConnected Will Call This Func***************/
//void Widget::slot_SshConnected()
//{
//    ui->m_text_Ssh_Status->append("SshConnected");
//    m_process = m_connection->createRemoteShell();
//    connect(m_process.data(), SIGNAL(readyRead()), this, SLOT(slot_SshReadyRead()));
//    connect(m_process.data(), SIGNAL(started()), this, SLOT(slot_SshStarted()));
//    connect(m_process.data(), SIGNAL(readyReadStandardOutput()),this, SLOT(slot_SshReadyReadStandarOutput()));
//    connect(m_process.data(), SIGNAL(readyReadStandardError()), this, SLOT(slot_SshReadReadStandarError()));
//    connect(m_process.data(), SIGNAL(closed(int)), this, SLOT(slot_SshMProcessClosed()));

//    m_process.data()->start();
//    ui->m_btn_connect->setEnabled(false);
//}
//void Widget::slot_SshReadReadStandarError()
//{
//    ui->m_text_Ssh_Status->append("SshReadyReadStandarOutput");
//}

/******Ssh Output Here********/
//void Widget::slot_SshReadyReadStandarOutput()
//{
//    QString str = m_process.data()->readAllStandardOutput().data();
//    str.chop(2);
//    //ui->m_text_Ssh_Status->append(m_process.data()->readAllStandardOutput().data());
//    ui->m_text_Ssh_Status->append(str);
////    QTextCursor cur = ui->m_text_Ssh_Status->textCursor();
////    cur.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
////    ui->m_text_Ssh_Status->setCursor(cur);
//    //ui->m_text_Ssh_Status->foc;
//}

//void Widget::slot_SshError(QSsh::SshError m_Ssherror)
//{
//    qDebug() << "xyfish! SshError!" << m_Ssherror;
//    ui->m_text_Ssh_Status->append("SshError");

//}

//void Widget::slot_SshDisconnected()
//{
//    //qDebug() << "xyfish! SshDisconnected";
//    ui->m_text_Ssh_Status->append("SshDisconnected");
//}

/*********May Not Effect************/
//void Widget::slot_SshDataAvailable(const QString &message)
//{

//    ui->m_text_Ssh_Status->append("data aviliable");
//    ui->m_text_Ssh_Status->append(message);
//}
/********When Ssh Have Data To Read, This Func Will Be Called************/
//void Widget::slot_SshReadyRead()
//{
//    //qDebug() << "data: " << m_process.data()->readAll();
//    //ui->m_text_Ssh_Status->append(m_process.data()->readAll());
//    //ui->m_text_Ssh_Status->append("SshReadRead");
//}
/**********Widget Connect Button Clicked*************/
void Widget::on_m_btn_connect_clicked(bool checked)
{

    mySsh::sshInfo tmp_info;
    tmp_info.userName = ui->m_line_username->text();
    tmp_info.password = ui->m_line_pwd->text();
    tmp_info.verifyType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    tmp_info.port = ui->m_line_port->text().toInt();
    tmp_info.timeout = 10;
    tmp_info.host = ui->m_line_ip->text();


    m_ssh->f_setSshInfo(tmp_info);
    m_ssh->f_connectSshServer();

}
/**********Widget Quit Button Clicked****************/
void Widget::on_m_btn_quit_clicked(bool checked)
{
    //m_ssh->f_sendSshMessage("ls\n");
    exit(0);
}
/********When Ssh Closed This Func Will Be Called**********/
//void Widget::slot_SshMProcessClosed()
//{
//    ui->m_text_Ssh_Status->append("m_processClosed");
//}

void Widget::slot_InputCmdLineReturnPressed()
{
    //if(ui->m_line_inputcmd->text().length())
    //{
//        m_process.data()->write(ui->m_line_inputcmd->text().toUtf8());
//        m_process.data()->write("\n");
        QString sendMsg = ui->m_line_inputcmd->text();
        sendMsg.append("\n");
        m_ssh->f_sendSshMessage(sendMsg);
        ui->m_line_inputcmd->clear();
    //}

    //m_process.data()->write()
    //ui->m_text_Ssh_Status->append("input return pressed");

}

void Widget::slot_SshMessageShowUi(QString msg)
{
    //QString msgSend = msg;
    msg.replace("\r", "");
    //msg.chop(1);
    qDebug() << msg;
    ui->m_text_Ssh_Status->append(msg);

}



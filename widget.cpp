#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
#include "QThread"
#include "myqthread.h"
#include "QTextCursor"
#include "sshfileconfigure.h"
#include "QTabWidget"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_ssh = new mySsh;

    m_fileConfig = new sshFileConfigure;



    connect(ui->m_line_inputcmd, SIGNAL(returnPressed()), this, SLOT(slot_InputCmdLineReturnPressed()));
    connect(m_ssh, SIGNAL(sgn_msgShowUI(QString)), this, SLOT(slot_SshMessageShowUi(QString)));
    connect(m_fileConfig, SIGNAL(sgn_readUserConfigureOK(mySsh::sshInfo)), this, SLOT(slot_readUserConfigureOK(mySsh::sshInfo)));

    m_fileConfig->f_getSshUserConfigure();
    testfunc();
}



Widget::~Widget()
{
    delete ui;
    delete m_thread;

}

void Widget::testfunc()
{
    //ui->m_tab_debug->addTab(NULL, "HELLO");
    QPushButton *btn1 = new QPushButton;
    btn1->setText("push me");
    //ui->m_tab_debug->addTab(btn1, "eoo");
    ui->m_tab_debug->setTabText(0, "bcm");
    ui->m_tab_debug->setTabText(1, "tcm");
    //ui->m_tab_debug->settab
}

void Widget::slot_readUserConfigureOK(mySsh::sshInfo myinfo)
{
    qDebug() << "readUserConfigureOK";
    ui->m_line_ip->setText(myinfo.host);

    ui->m_line_port->setText(QString::number( myinfo.port));
    ui->m_line_pwd->setText(myinfo.password);
    ui->m_line_username->setText(myinfo.userName);

}

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
    exit(0);
}


void Widget::slot_InputCmdLineReturnPressed()
{

        QString sendMsg = ui->m_line_inputcmd->text();
        sendMsg.append("\n");
        m_ssh->f_sendSshMessage(sendMsg);
        ui->m_line_inputcmd->clear();


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





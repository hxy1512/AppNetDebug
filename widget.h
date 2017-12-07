#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "include/QSsh"
#include <QThread>
#include "myqthread.h"
#include "QKeyEvent"
#include "QTextCursor"
#include "QFile"
#include "QPushButton"
#include "myssh.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void f_OpenSshConfig();
    ~Widget();

private:
    Ui::Widget *ui;
    myQThread *m_thread;
    QSsh::SshConnectionParameters m_params;
    QSsh::SshConnection * m_connection;
    QSharedPointer<QSsh::SshRemoteProcess> m_process;
    QFile *m_file;
    QPushButton *btn_test;
    mySsh *m_ssh;
signals:

private slots:
//    void slot_SshConnected();
//    void slot_SshError(QSsh::SshError);
//    void slot_SshDisconnected();
//    void slot_SshDataAvailable(const QString &message);
    void on_m_btn_connect_clicked(bool checked);
//    void slot_SshReadyRead();
//    void slot_SshStarted();
//    void slot_SshReadyReadStandarOutput();
//    void slot_SshReadReadStandarError();
    void on_m_btn_quit_clicked(bool checked);
//    void slot_SshMProcessClosed();
    void slot_InputCmdLineReturnPressed();
protected:
    //void keyPressEvent(QKeyEvent *key_event);
};

#endif // WIDGET_H

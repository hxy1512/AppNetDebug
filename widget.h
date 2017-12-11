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
#include "sshfileconfigure.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    //void f_OpenSshConfig();
    ~Widget();
    void testfunc();

private:
    Ui::Widget *ui;
    myQThread *m_thread;//  not use

    QFile *m_file;
    QPushButton *btn_test;
    mySsh *m_ssh;
    sshFileConfigure *m_fileConfig;
signals:

private slots:
    void slot_readUserConfigureOK(mySsh::sshInfo myinfo);
    void on_m_btn_connect_clicked(bool checked);
    void on_m_btn_quit_clicked(bool checked);
    void slot_InputCmdLineReturnPressed();
    void slot_SshMessageShowUi(QString msg);
    //void slot_testSlot();
protected:

};

#endif // WIDGET_H

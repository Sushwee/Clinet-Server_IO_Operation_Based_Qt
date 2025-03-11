#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

    QTcpServer *msgServer;               // 消息服务器
    QTcpServer *fileServer;              // 文件服务器
    QList<QTcpSocket*> msgClients;       // 消息客户端列表
    QList<QTcpSocket*> fileClients;      // 文件客户端列表

    // 文件接收相关
    QFile *receivedFile;                 // 接收的文件对象
    qint64 totalFileSize;                // 文件总大小
    qint64 receivedFileSize;             // 已接收大小
    QString currentFileName;             // 当前文件名

    QString getDateTime();               // 获取当前时间

private slots:
    void onNewMessageConnection();       // 新消息连接
    void onNewFileConnection();          // 新文件连接
    void onMessageReadyRead();           // 消息数据读取
    void onFileReadyRead();              // 文件数据读取
    void onMessageClientDisconnected();  // 消息连接断开
    void onFileClientDisconnected();     // 文件连接断开

};
#endif // DIALOG_H

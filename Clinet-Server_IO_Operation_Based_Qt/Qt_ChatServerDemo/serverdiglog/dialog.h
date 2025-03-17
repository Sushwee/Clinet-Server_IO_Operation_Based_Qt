#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QHash>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>

#define PORT 8080

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

    QTcpServer *msgServer;                 // 消息服务器
    QTcpServer *fileServer;                // 文件服务器
    QList<QTcpSocket*> m_connectedClient;  // 保存所有客户端socket
    QTcpSocket *serSocket_sendMsg;         // 用于发送消息的套接字

    QHash<QTcpSocket *, QFile *> m_ReceivingFiles;  // 客户端套接字与文件对象的映射
    QHash<QTcpSocket *, qint64> m_FileSizes;        // 客户端文件的总大小
    QHash<QTcpSocket *, qint64> m_BytesReceived;    // 客户端已接收的字节数


    QString getDateTime();               // 获取当前时间
    bool isFileTransferHeader(const QByteArray &data);                                  // 是否为头文件
    void OnSocketReadyFunc();                                                           // 读取客户端socket传输的数据信息
    void handleFileTransferHeader(QTcpSocket *clientSocket, const QByteArray &data);    // 处理头消息
    void handleMessageData(QTcpSocket *clientSocket, const QByteArray &data);           // 处理消息主体
    void handleFileContentReceive(QTcpSocket *clisocket);                               // 接收文件内容

private slots:
    void onNewConnection();                                            // 处理客户端新连接
    void onClientReadyRead();                                          // 实现从客户端读取数据的逻辑
    void procRecvData(QTcpSocket *clisocket, const QByteArray &data);  // 解析接受的数据
    void on_pushButton_Listen_clicked();
    void on_pushButton_StopListten_clicked();
    void on_pushButton_StopListen_clicked();
    void on_pushButton_SenMsg_clicked();
};
#endif // DIALOG_H

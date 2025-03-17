#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QTcpSocket>
#include <QFile>        // 专门用于读取和写入文件
#include <QFileDialog>  // 文件对话框头文件
#include <QHostAddress> // 用于处理IP地址、主机地址等操作
#include <QHostInfo>
#include <QMessageBox>
#include <QLabel>
#include <QDateTime>
#include <QPainter>     // 用于绘制图形和图像工具类

// 系统托盘的头文件
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>           // 右键图表显示菜单


QT_BEGIN_NAMESPACE
namespace Ui {
class MainDialog;
}
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

    QString getDateTime();

private:
    QTcpSocket *m_TcpMsgClient;  // 处理聊天消息socket
    QTcpSocket *m_TcpFileClient; // 处理文件传输消息socket

    QFile *m_LocalFiles;         // 要传输的文件
    qint64 m_TotalBytes;         // 数据总大小
    qint64 m_BytesWrite;         // 已经发送数据大小
    qint64 m_BytesToWrite;       // 剩下数据大小
    qint64 m_LoadSizes;          // 每次发送数据的大小
    QString m_FileName;          // 保存文件信息

    QByteArray m_OutDataBlock;   // 数据缓冲区（即存放每次要发送的数据）

    void paintEvent(QPaintEvent *event);                  // 绘制背景图
    QString GetLocalIPAddress();                          // 获取本机的IP地址信息
    void CloseEvent(QCloseEvent *event);                  // 关闭事件
    QString getFileNameOnly(const QString &fullPath);     // 返回不带路径的文件名

    // 系统托盘
    QSystemTrayIcon *MySystemTray;  // 托盘指针
    QMenu           *pContextMenu;  // 托盘菜单
    QAction         *qMiniAct;      // 客户端最小化
    QAction         *qRestoreAct;   // 恢复客户端
    QAction         *qExit;         // 退出系统


private slots:
    void OnConnectedFunc();                               // 客户端连接服务器
    void OnDisconnectedFunc();                            // 客户端与服务器断开
    void OnSocketReadyFunc();                             // 读取服务器socket传输的数据信息

    void SystemTrayFunc();                                // 系统托盘函数
    void UpdateClientProgress(qint64);                    // 更新进度条
    void DisplayErrorFunc(QAbstractSocket::SocketError);  // 异常处理信息


    void on_pushButton_ConnectServer_clicked();

    void on_pushButton_Disconnect_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Clear_clicked();

    void on_pushButton_SendMsg_clicked();

    void on_pushButton_SelectFile_clicked();

    void on_pushButton_SendFile_clicked();

private:
    Ui::MainDialog *ui;
};
#endif // MAINDIALOG_H

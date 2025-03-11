#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , receivedFile(nullptr)
    , totalFileSize(0)
    , receivedFileSize(0)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    // 初始化消息服务器（端口：12345）
    msgServer = new QTcpServer(this);
    if (!msgServer->listen(QHostAddress::Any, 12345)) {
        QMessageBox::critical(this, "错误", "消息端口监听失败: " + msgServer->errorString());
        close();
    }

    // 初始化文件服务器（端口：12346）
    fileServer = new QTcpServer(this);
    if (!fileServer->listen(QHostAddress::Any, 12346)) {
        QMessageBox::critical(this, "错误", "文件端口监听失败: " + fileServer->errorString());
        close();
    }

    // 连接信号槽
    connect(msgServer, &QTcpServer::newConnection, this, &ServerDialog::onNewMessageConnection);
    connect(fileServer, &QTcpServer::newConnection, this, &ServerDialog::onNewFileConnection);

    ui->plainTextEdit_MsgList->appendPlainText("[服务端已启动]");
    ui->plainTextEdit_MsgList->appendPlainText("消息端口: 12345");
    ui->plainTextEdit_MsgList->appendPlainText("文件端口: 12346");
}

Dialog::~Dialog()
{
    delete ui;

    if (receivedFile)
    {
        receivedFile->close();
        delete receivedFile;
    }
}

// 新消息连接
void ServerDialog::onNewMessageConnection()
{
    QTcpSocket *clientSocket = msgServer->nextPendingConnection();
    msgClients.append(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerDialog::onMessageReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerDialog::onMessageClientDisconnected);
    ui->plainTextEdit_MsgList->appendPlainText("[客户端连接] " + clientSocket->peerAddress().toString());
}


// 新文件连接
void ServerDialog::onNewFileConnection()
{
    QTcpSocket *clientSocket = fileServer->nextPendingConnection();
    fileClients.append(clientSocket);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerDialog::onFileReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerDialog::onFileClientDisconnected);
    ui->plainTextEdit_MsgList->appendPlainText("[文件传输连接] " + clientSocket->peerAddress().toString());
}

// 处理消息数据
void ServerDialog::onMessageReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    while (clientSocket->canReadLine()) {
        QString message = QString::fromUtf8(clientSocket->readLine()).trimmed();
        ui->plainTextEdit_MsgList->appendPlainText("[消息 " + getDateTime() + "] " + message);

        // 广播消息给所有客户端
        for (QTcpSocket *otherClient : msgClients) {
            if (otherClient != clientSocket && otherClient->state() == QTcpSocket::ConnectedState) {
                otherClient->write(QString("[服务器转发] " + message + "\n").toUtf8());
            }
        }
    }
}

// 处理文件数据
void ServerDialog::onFileReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_15);

    if (receivedFileSize == 0) { // 接收文件头
        if (clientSocket->bytesAvailable() < sizeof(qint64) * 2) return;

        in >> totalFileSize >> receivedFileSize >> currentFileName;

        // 选择保存路径
        QString savePath = QFileDialog::getSaveFileName(this, "保存文件", currentFileName);
        if (savePath.isEmpty()) {
            clientSocket->disconnectFromHost();
            return;
        }

        receivedFile = new QFile(savePath);
        if (!receivedFile->open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "错误", "无法创建文件");
            delete receivedFile;
            receivedFile = nullptr;
            clientSocket->disconnectFromHost();
            return;
        }

        ui->plainTextEdit_MsgList->appendPlainText("开始接收文件: " + currentFileName);
        ui->progressBar->setMaximum(totalFileSize);
        ui->progressBar->setValue(0);
    } else { // 接收文件内容
        QByteArray buffer = clientSocket->readAll();
        receivedFile->write(buffer);
        receivedFileSize += buffer.size();
        ui->progressBar->setValue(receivedFileSize);

        if (receivedFileSize == totalFileSize) {
            receivedFile->close();
            delete receivedFile;
            receivedFile = nullptr;
            receivedFileSize = 0;
            totalFileSize = 0;
            ui->plainTextEdit_MsgList->appendPlainText("文件接收完成: " + currentFileName);
            clientSocket->disconnectFromHost();
        }
    }
}

// 消息客户端断开
void ServerDialog::onMessageClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        msgClients.removeOne(clientSocket);
        clientSocket->deleteLater();
        ui->plainTextEdit_MsgList->appendPlainText("[客户端断开] " + clientSocket->peerAddress().toString());
    }
}

// 文件客户端断开
void ServerDialog::onFileClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        fileClients.removeOne(clientSocket);
        clientSocket->deleteLater();
        if (receivedFile) {
            receivedFile->close();
            delete receivedFile;
            receivedFile = nullptr;
        }
        ui->plainTextEdit_MsgList->appendPlainText("[文件传输断开] " + clientSocket->peerAddress().toString());
    }
}

// 获取时间戳
QString ServerDialog::getDateTime()
{
    return QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
}




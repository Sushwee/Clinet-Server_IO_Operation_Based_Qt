#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    serSocket_sendMsg = new QTcpSocket(this);

    ui->pushButton_StopListen->setEnabled(false);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_Listen_clicked()
{

    msgServer = new QTcpServer(this);
    QString ip = ui->IPlineEdit->text();
    quint16 port = ui->PortspinBox->value();

    if(msgServer->listen(QHostAddress(ip), port)) // 监听成功
    {
        ui->plainTextEdit_MsgList->appendPlainText(QString("服务器已启动监听, IP:%1, 端口:%2").arg(ip).arg(port));
        ui->pushButton_Listen->setEnabled(false);
        ui->pushButton_StopListen->setEnabled(true);
    }

    connect(msgServer, &QTcpServer::newConnection, this, &Dialog::onNewConnection);
}


void Dialog::onNewConnection()
{
    QTcpSocket *cliSocket = msgServer->nextPendingConnection();
    m_connectedClient.append(cliSocket);

    connect(cliSocket, &QTcpSocket::readyRead, this, &Dialog::onClientReadyRead);
}


void Dialog::onClientReadyRead()
{
    QTcpSocket *clisocket = qobject_cast<QTcpSocket *>(sender());
    if (!clisocket)return;

    // 读取数据
    QByteArray data = clisocket->readAll();

    // 解析数据
    procRecvData(clisocket, data);

    // 检查是否正在接收文件
    if (m_ReceivingFiles.contains(clisocket))  // 如果正在接收文件，继续接收文件内容
    {
        handleFileContentReceive(clisocket);
    }
    else                                          // 否则，按普通数据处理
    {
        procRecvData(clisocket, clisocket->readAll());
    }

}


void Dialog::procRecvData(QTcpSocket *clisocket, const QByteArray &data)
{
    // 判断数据类型并处理
    if (isFileTransferHeader(data)) // 如果是文件传输的头部信息
    {
        handleFileTransferHeader(clisocket, data);
    }
    else
    {
        // 如果是普通消息
        handleMessageData(clisocket, data);
    }
}


bool Dialog::isFileTransferHeader(const QByteArray &data)
{
    return data.startsWith("FILE_TRANSFER_HEADER"); // 例如：检查数据是否包含特定的文件传输标识符
}


void Dialog::handleFileTransferHeader(QTcpSocket *clisocket, const QByteArray &data)
{
    // 解析文件传输头部信息
    // 例如：文件名、文件大小等
    QDataStream stream(data);
    stream.setVersion(QDataStream::Qt_5_15);

    QString fileName;
    qint64 fileSize;
    stream >> fileName >> fileSize;

    // 记录文件信息
    ui->plainTextEdit_MsgList->appendPlainText(QString("收到文件传输请求: 文件名=%1, 大小=%2字节")
                                                  .arg(fileName)
                                                  .arg(fileSize));

    // 准备接收文件内容
    QFile *file = new QFile(fileName, this);
    if (!file->open(QIODevice::WriteOnly))
    {
        ui->plainTextEdit_MsgList->appendPlainText(QString("无法打开文件 %1 进行写入").arg(fileName));
        return;
    }

    // 保存文件指针和相关信息
    m_ReceivingFiles[clisocket] = file;
    m_FileSizes[clisocket] = fileSize;
    m_BytesReceived[clisocket] = 0;

    // 通知客户端可以开始传输文件内容
    QByteArray response;
    QDataStream out(&response, QIODevice::WriteOnly);
    out << "FILE_TRANSFER_READY";
    clisocket->write(response);
}


void Dialog::handleMessageData(QTcpSocket *clisocket, const QByteArray &data)
{
    QString message = QString::fromUtf8(data);
    ui->plainTextEdit_MsgList->appendPlainText(QString("收到客户端消息: %1").arg(message));
}


void Dialog::handleFileContentReceive(QTcpSocket *clisocket)
{
    // 获取文件指针和相关信息
    QFile *file = m_ReceivingFiles[clisocket];
    qint64 fileSize = m_FileSizes[clisocket];
    qint64 &bytesRecv = m_BytesReceived[clisocket];

    // 读取数据并写入文件
    QByteArray data = clisocket->readAll();
    if(file->write(data) != data.size())
    {
        ui->plainTextEdit_MsgList->appendPlainText("写入文件错误");
        file->close();
        file->remove();
        file->deleteLater();
        m_ReceivingFiles.remove(clisocket);
        m_FileSizes.remove(clisocket);
        m_BytesReceived.remove(clisocket);
        return;
    }

    bytesRecv += data.size();

    // 检查是否接收完整个文件
    if(bytesRecv == fileSize)
    {
        file->close();
        ui->plainTextEdit_MsgList->appendPlainText(QString("%1接收完成").arg(file->fileName()));
        file->deleteLater();
        m_ReceivingFiles.remove(clisocket);
        m_FileSizes.remove(clisocket);
        m_BytesReceived.remove(clisocket);
    }
    else if(bytesRecv > fileSize)
    {
        ui->plainTextEdit_MsgList->appendPlainText("文件接收异常：接收数据超过预期大小。");
        file->close();
        file->remove();
        file->deleteLater();
        m_ReceivingFiles.remove(clisocket);
        m_FileSizes.remove(clisocket);
        m_BytesReceived.remove(clisocket);
    }

}


void Dialog::OnSocketReadyFunc()
{

}

void Dialog::on_pushButton_StopListen_clicked()
{
    // 先检查是否正在监听
    if(msgServer->isListening())
    {
        msgServer->close();
        ui->plainTextEdit_MsgList->appendPlainText("服务器已停止监听");

        ui->pushButton_Listen->setEnabled(true);
        ui->pushButton_StopListen->setEnabled(false);
    }
    else ui->plainTextEdit_MsgList->appendPlainText("服务器未启动监听");
}


void Dialog::on_pushButton_SenMsg_clicked()
{
    QString msg = ui->plainTextEdit_SendMsg->toPlainText();

    if(msg.isEmpty())
    {
        QMessageBox::critical(this, "错误", "发送消息不能为空", QMessageBox::Yes);
    };

    // 发送消息时遍历所有客户端


    // 将用户发送的消息显示到消息列表控件
    ui->plainTextEdit_MsgList->appendPlainText("服务端消息：" + msg);
    ui->plainTextEdit_SendMsg->clear();
    ui->plainTextEdit_SendMsg->setFocus();

    QByteArray byteArray = msg.toUtf8();
    for(auto soc : m_connectedClient) soc->write(byteArray);
    //serSocket_sendMsg->write(byteArray);
}


#include "maindialog.h"
#include "ui_maindialog.h"

#define MAX_FILE_SIZE 100 * 1024 * 1024

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);

    //固定窗口高度和宽度
    setFixedSize(width(), height()); // 固定尺寸是以用户设计为准

    m_TcpMsgClient = new QTcpSocket(this);
    m_TcpFileClient = new QTcpSocket(this);

    m_TotalBytes = 0;
    m_BytesWrite = 0;
    m_BytesToWrite = 0;
    m_LoadSizes = 4 * 1024;

    // 获取本机的IP地址
    QString strLocalIPs = GetLocalIPAddress();

    // 将返回的IP地址显示到combo box组合框控件里面来
    ui->comboBox_ServerIP->addItem(strLocalIPs);

    // 禁止按钮点击
    //ui->pushButton_Disconnect->setEnabled(false);
    //ui->pushButton_SendFile->setEnabled(false);

    connect(m_TcpMsgClient, SIGNAL(connected()), this, SLOT(OnConnectedFunc()));
    connect(m_TcpMsgClient, SIGNAL(disconnected()), this, SLOT(OnDisconnectedFunc()));
    connect(m_TcpMsgClient, SIGNAL(readyRead()), this, SLOT(OnSocketReadyFunc()));

    // 当有数据发送成功时，更新进度条状态
    connect(m_TcpFileClient, SIGNAL(bytesWritten(qint64)), this, SLOT(UpdateClientProgress(qint64)));

    // 文件传输错误处理(例如发生IP或端口错误时)
    connect(m_TcpFileClient, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(DisplayErrorFunc(QAbstractSocket::SocketError)));

    // 禁止用户编辑消息列表
    ui->plainTextEdit_MsgList->setReadOnly(true);

    // 调用系统托盘函数
    SystemTrayFunc();
}

MainDialog::~MainDialog()
{
    delete ui;
}


// 更改窗口背景
void MainDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/new/prefix1/image/bg.jpg"), QRect());
}


QString MainDialog::GetLocalIPAddress()
{
    QString strHostName = QHostInfo::localHostName();       // 获取本地主机名称
    QHostInfo HostInfo = QHostInfo::fromName(strHostName);  // 通过主机名称获取IP

    QString strLocalIP = "";
    QList<QHostAddress> addressList = HostInfo.addresses(); // 获取所有本机网络接口的IP地址列表

    if(!addressList.isEmpty())
    {
        for(int i = 0; i < addressList.count(); i++)
        {
            QHostAddress sHost = addressList.at(i);         // 从addressList列表中获取第i个元素

            // 判断本机IP协议是否为IPV4
            if(QAbstractSocket::IPv4Protocol == sHost.protocol())
            {
                strLocalIP = sHost.toString();
                break;
            }
        }
    }

    return strLocalIP;
}


void MainDialog::CloseEvent(QCloseEvent *event)
{


    event->accept();
}


void MainDialog::OnConnectedFunc()    // 客户端连接服务器后要设置的
{
    ui->plainTextEdit_MsgList->appendPlainText("[-----客户端与服务器连接成功-----]");
    ui->plainTextEdit_MsgList->appendPlainText("IP:"+m_TcpMsgClient->peerAddress().toString()
                                               + "Port:"+ QString::number(m_TcpMsgClient->peerPort()));

    // 连接完后设置按钮使用
    ui->pushButton_Disconnect->setEnabled(true);
    ui->pushButton_ConnectServer->setEnabled((false));
}


void MainDialog::OnDisconnectedFunc()
{
    ui->plainTextEdit_MsgList->appendPlainText("[客户端与服务器连接已断开]");

    ui->pushButton_ConnectServer->setEnabled(true);
    ui->pushButton_Disconnect->setEnabled((false));
}


void MainDialog::OnSocketReadyFunc()  // 读取服务器socket传输的数据信息
{
    while(m_TcpMsgClient->canReadLine())
    {
        ui->plainTextEdit_MsgList->appendPlainText("[服务器消息 " + getDateTime() + "] " +m_TcpMsgClient->readLine());
    }
}


void MainDialog::SystemTrayFunc()
{
    // 托盘显示图标
    QIcon qIcon(":/new/prefix1/image/logo.jpg");
    MySystemTray = new QSystemTrayIcon(this);
    MySystemTray->setIcon(qIcon);

    // 提示消息
    MySystemTray->setToolTip("tcp客户端");

    qMiniAct = new QAction("客户端最小化", this);
    connect(qMiniAct, SIGNAL(triggered()), this, SLOT(hide()));           // 隐藏客户端

    qRestoreAct = new QAction("恢复客户端", this);
    connect(qRestoreAct, SIGNAL(triggered()), this, SLOT(showNormal()));  // 显示客户端窗口

    qExit = new QAction("退出客户端", this);
    connect(qExit, SIGNAL(triggered()), this, SLOT(quit()));

    // 将QAction对象添加到菜单
    pContextMenu = new QMenu(this);
    pContextMenu->addAction(qMiniAct);
    pContextMenu->addAction(qRestoreAct);
    pContextMenu->addAction(qExit);

    // 设置指定菜单为系统托盘的上下文菜单
    MySystemTray->setContextMenu(pContextMenu);

    // 显示系统托盘
    MySystemTray->show();
}


void MainDialog::UpdateClientProgress(qint64 numBytes)
{
    // 确认已发送数据的大小
    m_BytesWrite += (int)numBytes;

    if(m_BytesToWrite > 0)
    {
        // 从文件当中取出数据到发送缓冲区，每次发送文件大小的数据，设置为4KB;
        // 如果剩下的数据不满足4KB，就发送剩下数据大小;
        // qMin(m_BytesToWrite, m_LoadSizes)确保了一次最多读取m_LoadSizes字节的数据，
        // 或者根据剩余需要发送的数据量m_BytesToWrite来决定实际读取的字节数。
        m_OutDataBlock = m_LocalFiles->read(qMin(m_BytesToWrite, m_LoadSizes));

        // 从发送缓冲区发送数据，计算发送完一次数据后还剩下数据的大小
        m_BytesToWrite -= (int)m_TcpFileClient->write(m_OutDataBlock);

        // 清空缓冲区
        m_OutDataBlock.resize(0);
    }
    else
    {
        m_LocalFiles->close(); // 关闭文件
    }

    // 更新进度条状态
    ui->progressBar->setMaximum((m_TotalBytes));
    ui->progressBar->setValue(m_BytesWrite);


    // 发送完成后
    if(m_BytesWrite == m_TotalBytes)
    {
        ui->plainTextEdit_MsgList->appendPlainText(QString("------文件发送成功------"));
        m_LocalFiles->close();
    }

}


void MainDialog::DisplayErrorFunc(QAbstractSocket::SocketError)
{
    // 文件传输错误提示（此处略）
    m_TcpFileClient->close();
    ui->progressBar->reset();
}


void MainDialog::on_pushButton_ConnectServer_clicked()
{
    // 获取IP地址和端口
    QString IpAdress = ui->comboBox_ServerIP->currentText();
    quint16 Port = ui->spinBox_ServerPort->value();

    // 连接服务器处理操作
    m_TcpMsgClient->connectToHost(IpAdress, Port);
}


void MainDialog::on_pushButton_Disconnect_clicked()
{
    // 关闭套接字
    if(m_TcpMsgClient->state() == QAbstractSocket::ConnectedState)
        m_TcpMsgClient->disconnectFromHost();

    /*if(m_TcpFileClient->state() == QAbstractSocket::ConnectedState)
        m_TcpFileClient->disconnectFromHost();*/
}


void MainDialog::on_pushButton_Exit_clicked()
{
    // 退出系统则关闭套接字
    m_TcpFileClient->close();
    m_TcpMsgClient->close();
    this->close();
}


void MainDialog::on_pushButton_Clear_clicked()
{
    ui->plainTextEdit_MsgList->clear();
}


void MainDialog::on_pushButton_SendMsg_clicked()
{ 
    // 获取多行编辑器控件，用户所输入的消息
    QString strMsg = ui->plainTextEdit_SendMsg->toPlainText();

    if(strMsg.isEmpty())
    {
        QMessageBox::critical(this, "错误", "发送信息不能为空，请重新检查。", QMessageBox::Yes);
        ui->plainTextEdit_SendMsg->setFocus();  // 将光标焦点定位到用户输入控件
        return;
    }

    // 将用户发送的消息显示到消息列表控件
    ui->plainTextEdit_MsgList->appendPlainText("[客户端消息 " + getDateTime() + "] " + strMsg);
    ui->plainTextEdit_SendMsg->clear();     // 发送完清空发送消息框
    ui->plainTextEdit_SendMsg->setFocus();

    // QByteArray用于处理字节数组的类，可以存储和访问二进制数据、图像、音频。
    QByteArray byteArray = strMsg.toUtf8();
    byteArray.append('\n');  // 换行

    // 将数据信息发送至服务端
    m_TcpMsgClient->write(byteArray);
}


void MainDialog::on_pushButton_SelectFile_clicked()
{
    // 打开一个文件对话框，允许用户选择一个文件，并将所选文件的路径存储在m_FileNames变量中
    m_FileName = QFileDialog::getOpenFileName(this, "请选择要传输的文件");
    if(!m_FileName.isEmpty())
    {
        //%1表示第一个参数的位置，它会被 .arg(m_FileName)方法提供的值替换
        ui->plainTextEdit_MsgList->appendPlainText(
            (QString("[客户端打开文件 '%1' 成功 %2]").arg(getFileNameOnly(m_FileName)).arg(getDateTime()))
            );
        ui->pushButton_SendFile->setEnabled(true);
    }

}


void MainDialog::on_pushButton_SendFile_clicked()
{
    m_LocalFiles = new QFile(m_FileName);
    if(!m_LocalFiles->open(QFile::ReadOnly))
    {
        qDebug() << "打开文件错误，请重新检查。";
        return;
    }

    m_TotalBytes = m_LocalFiles->size();  // 获取发送文件的大小

    if(m_TotalBytes > MAX_FILE_SIZE)
    {
        qDebug() << QString("文件太大无法发送，最大允许大小为 %1 MB").arg(MAX_FILE_SIZE/1024/1024);
        m_LocalFiles->close();
        delete m_LocalFiles;
        return;
    }

    QDataStream sendOut(&m_OutDataBlock, QIODevice::WriteOnly); // 将数据序列化并写入到 m_OutDataBlock
    QString strCurrentFileName = m_FileName.right(m_FileName.size()-m_FileName.lastIndexOf('/') - 1);

    // 依次写入文件总大小信息空间、文件名大小信息空间、文件名到sendOut
    sendOut<<qint64(0)<<qint64(0)<<strCurrentFileName;

    // 总大小是文件名大小等信息和实际文件大小的总和
    m_TotalBytes += m_OutDataBlock.size();
    sendOut.device()->seek(0); // 将QDataStream的设备指针回溯到起始位置，以便更新之前的占位符

    sendOut << m_TotalBytes << qint64((m_OutDataBlock.size()-sizeof(qint64)*2));
    /* 更新第一个占位符为m_TotalBytes，即整个数据块的总大小；
      更新第二个占位符, 该处表示有效数据部分的大小。m_OutDataBlock包含了之前
     写入的一些头部信息（例如两个 qint64 占位符），所以需要减去这些占位符所占用的空间。*/

    // 发送完后剩下头部数据的大小
    m_BytesToWrite = m_TotalBytes - m_TcpFileClient->write((m_OutDataBlock));
    m_OutDataBlock.resize(0);
}


QString MainDialog::getDateTime()
{
    QDateTime CurTime = QDateTime::currentDateTime();          // 获取当前日期与时间
    QString strYear = QString::number(CurTime.date().year());  // 从日期中获取年
    QString strMon = QString::number(CurTime.date().month());
    QString strDay = QString::number(CurTime.date().day());
    QString strHour = QString::number(CurTime.time().hour());
    QString strMin = QString::number(CurTime.time().minute());
    QString strSec = QString::number(CurTime.time().second());
    QString strDateTime = strYear + "/" + strMon + "/" + strDay + " " + strHour + ":" + strMin + ":" + strSec;
    return strDateTime;
}


QString MainDialog::getFileNameOnly(const QString &fullPath)
{
    QFileInfo fileInfo(fullPath);
    return fileInfo.fileName();
}

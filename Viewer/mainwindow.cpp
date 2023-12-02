#include <QLineEdit>
#include <QDir>
#include <thread>
#include <MessagesUpdateEvent.h>
#include <Socket/ConnResetException.h>
#include <IMessagePack.h>
#include <TextMessage.h>
#include <FileMessage.h>
#include <UtilFile.h>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signindialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL (released()),this, SLOT (sendMessage()));    

    _is_connected.store(false);

    // register dialog
    SignInDialog *d = new SignInDialog(this);
    d->show();
    connect(d, &SignInDialog::SignInDialogAccepted, this, &MainWindow::signInDialogAccepted);
    connect(d, &SignInDialog::SignInDialogRejected, this, &MainWindow::signInDialogRejected);

    _client.AddObserver(this);

    std::thread thr([&]() {
        while (_is_connected.load())
        {
            _client.recv();
        }
    });
    thr.detach();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::signInDialogAccepted(QString url, QString user_name, QString password)
{
    // TODO: do authentication
    this->_url = url;
    this->_user_name = user_name;
    this->_password = password;
    while (_is_connected.load() == false)
    {
        tryToConnect();

        if (!_is_connected.load())
        {
            qDebug() << "Error: Can't connect by this URL\n\n";
            // register dialog
            SignInDialog d(this);
            d.show();
        }
    }
}

void MainWindow::signInDialogRejected()
{
    // register dialog
    SignInDialog d(this);
    d.show();
}

void MainWindow::sendMessage()
{
    auto msg = ui->textEdit->toPlainText().toStdString();
    auto &&url = _url.toStdString(), username = _user_name.toStdString(), password = _password.toStdString();
    AuthorizedMessage* msg_to_send = nullptr;
    format msg_format = fileExists(msg) ? file : text;
    switch (msg_format) {
    case text:
    {
        msg_to_send = new TextMessage(username, password, msg);
        break;
    }
    case file:
    {
        auto dot_befor_ext = msg.find_last_of('.');
        auto extension = msg.substr(dot_befor_ext);
        auto file_data = readFromFile(msg);
        msg_to_send = new FileMessage(username, password, extension, file_data);
        break;
    }
    default:
        assert(0);
        break;
    }
    _client.send(url, msg_to_send);
    delete[] msg_to_send;
}

void MainWindow::tryToConnect()
{
    _is_connected.store(_client.connect(_url.toStdString()));
}

void MainWindow::Update(const Event& e)
{
    switch (e.GetEventType())
    {
    case messagesUpdate:
    {
        auto&& msg = static_cast<const MessagesUpdateEvent&>(e).GetMsg();
        qDebug() << "New message\n";
        handleMessage(msg);
        break;
    }
    case connReset:
    {
        qDebug() << "Server disconnected\n";
        _is_connected.store(false);
        tryToConnect();
        break;
    }
    default:
        assert(0);
        break;
    }
}

void MainWindow::handleMessage(const IMessage& msg)
{
    switch (msg.GetFormat())
    {
    case text:
    {
        auto&& txt_msg = static_cast<const TextMessage&>(msg);
        _msg_pack->AddMsg(txt_msg);
        auto str = txt_msg.GetUsername() + txt_msg.GetMsg();
        ui->plainTextEdit->appendPlainText(QString::fromStdString(str));
        break;
    }
    case file:
    {
        auto&& file_msg = static_cast<const FileMessage&>(msg);
        auto&& file_name = createUniqueFileName(file_msg.GetExtension().c_str());
        fileWrite(file_name, file_msg.GetMsg().data(), file_msg.GetMsg().size());
        system(std::string("start " + file_name).c_str());
        // TODO хранить в FileMessage не расширение, а имя файла
        _msg_pack->AddMsg(FileMessage(file_msg.GetUsername(), file_msg.GetPassword(), file_msg.GetExtension(), file_name));
        auto str = file_msg.GetUsername() + file_name;
        ui->plainTextEdit->appendPlainText(QString::fromStdString(str));
        break;
    }
    case msgPack:
    {
        auto&& pack_msg = static_cast<const MessagePack&>(msg);
        for (auto&& m : pack_msg.GetMsgs())
        {
            handleMessage(*m);
        }
        break;
    }
    default:
        assert(0);
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <AppClient.h>
#include <IObserver.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void tryToConnect();
    void handleMessage(const IMessage& m);

private:
    Ui::MainWindow *ui;
    friend Client;
    QString _url, _user_name, _password;
    Client _client;
    std::atomic<bool> _is_connected;
    std::shared_ptr<IMessagePack> _msg_pack;

private slots:
    void signInDialogAccepted(QString url, QString user_name, QString password);
    void signInDialogRejected();
    void sendMessage();
    void update(QSharedPointer<Event> e);

};
#endif // MAINWINDOW_H

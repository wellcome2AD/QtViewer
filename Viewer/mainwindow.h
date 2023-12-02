#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <AppClient.h>
#include <IObserver.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IObserver
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void tryToConnect();
    virtual void Update(const Event& e) override;

private:
    Ui::MainWindow *ui;
    friend Client;
    std::string _url;
    Client _client;
    std::atomic<bool> is_connected;
    std::shared_ptr<IMessagePack> _msg_pack;

private slots:
    void sendMessage();
    void handleMessage(const IMessage& m);

};
#endif // MAINWINDOW_H

#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

class SignInDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SignInDialog(QWidget *parent);

private:
    QLabel *title;
    QLineEdit *url, *user_name, *password;

signals:
 void SignInDialogAccepted(QString url, QString user_name, QString password);
 void SignInDialogRejected();

private slots:
    void accept();
    void reject();
};

#endif // SIGNINDIALOG_H

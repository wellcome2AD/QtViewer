#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

#include "signindialog.h"

SignInDialog::SignInDialog(QWidget *parent) : QDialog(parent)
{
    // Use a layout allowing to have a label next to each field
    QFormLayout *form = new QFormLayout(this);
    // Add some text above the fields
    title = new QLabel("Sign in:");
    form->addRow(title);
    // Add the lineEdits with their respective labels
    QString value_labels[] = { "URL:", "User name:", "Password"};
    url = new QLineEdit("127.0.0.1:", this);
    user_name = new QLineEdit(this);
    password = new QLineEdit(this);
    form->addRow(value_labels[0], url);
    form->addRow(value_labels[1], user_name);
    form->addRow(value_labels[2], password);
    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);
    form->addRow(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SignInDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SignInDialog::reject);
}

void SignInDialog::accept()
{
    auto &&_url = url->text(), _user_name = user_name->text(), _password = password->text();
    if(!_url.isEmpty() && !_user_name.isEmpty() && !_password.isEmpty())
    {
        emit SignInDialogAccepted(_url, _user_name, _password);
        QDialog::accept();
    }
    else
    {
        title->setText("Error: incomplete data");
    }
}

void SignInDialog::reject()
{
    emit SignInDialogRejected();
}

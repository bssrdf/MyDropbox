#ifndef LOGIN_PAGE_CPP
#define LOGIN_PAGE_CPP

#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>
#include <iostream>
LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);

}

LoginPage::LoginPage(Client * _client , Socket& _csock) : ui(new Ui::LoginPage) {
    csock = _csock;
    client = _client;
    ui->setupUi(this); //necessary, I think.

}

LoginPage::~LoginPage()
{
    delete ui;
    this->client->handleExit();
}

void LoginPage::on_btn_ping_clicked()
{

    bool reply = this->client->eventHandler(PING_INSTR);
    QMessageBox msg;
    if (reply) {
        msg.setText("success!\n");
    } else {
        msg.setText("failure!\n");
    }
    msg.exec();
}

void LoginPage::on_btn_back_clicked()
{
    this->client->eventHandler(LOGIN_TO_CLIENT);
}


void LoginPage::on_btn_register_clicked()
{
    this->client->eventHandler(LOGIN_TO_REGISTER);
}


void LoginPage::on_btn_login_clicked()
{
    //Set the data.

    this->client->data.user.userID = (this->ui->txt_username)->text().toUtf8().constData();
    this->client->data.user.password = (this->ui->txt_password)->text().toUtf8().constData();

    bool checker=0;
    for (int i=0;i<this->client->data.user.userID.size();i++)
    {
        if (!isalnum(this->client->data.user.userID[i]))
        {
            checker=1;
            break;
        }
    }

    for (int i=0;i<this->client->data.user.password.size();i++)
    {
        if (!isalnum(this->client->data.user.password[i]))
        {
            checker=1;
            break;
        }
    }

    if (checker==0)
    {

        bool reply = this->client->eventHandler(LOGIN_TO_MAIN);
        if (reply) {
            this->client->showMain();
        } else {
            QMessageBox msg;
            msg.setText(" Invalid username/password ");
            msg.exec();
        }
    }
    else
    {
        QMessageBox::information(this,"Error","Invalid username/password(use only alphanumeric characters.");
    }
}

void LoginPage::on_txt_username_selectionChanged()
{
    this->ui->txt_username->setText("");
    this->ui->txt_password->setText("");
    this->ui->txt_password->setEchoMode(QLineEdit::Password);
}

#endif

#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setFixedSize(400, 300);
    setWindowTitle(tr("µÇÂ¼"));
    ui->pwdLineEdit->setFocus();
    ui->loginBtn->setDefault(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// µÇÂ¼°´Å¥
void LoginDialog::on_loginBtn_clicked()
{
    if (ui->pwdLineEdit->text().isEmpty()) {
        QMessageBox::information(this, tr("ÇëÊäÈëÃÜÂë"),
                                 tr("ÇëÏÈÊäÈëÃÜÂëÔÙµÇÂ¼£¡"), QMessageBox::Ok);
        ui->pwdLineEdit->setFocus();
    } else {
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if (query.value(0).toString() == ui->pwdLineEdit->text()) {
            QDialog::accept();
        } else {
            QMessageBox::warning(this, tr("ÃÜÂë´íÎó"),
                                 tr("ÇëÊäÈëÕýÈ·µÄÃÜÂëÔÙµÇÂ¼£¡"), QMessageBox::Ok);
            ui->pwdLineEdit->clear();
            ui->pwdLineEdit->setFocus();
        }
    }
}

// ÍË³ö°´Å¥
void LoginDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}

#include "verificationwidget.h"
#include "ui_verificationwidget.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QDir>
#include <decode.h>
#include <fstream>
#include <QString>
#include <QDebug>
#include "mainwindow.h"

QString VerificationWidget::password;

VerificationWidget::VerificationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VerificationWidget)
{
    ui->setupUi(this);
    QRegExp reg("[0-9a-zA-Z]{16}");
    ui->lineEdit->setValidator(new QRegExpValidator(reg,this));
}

VerificationWidget::~VerificationWidget()
{
    delete ui;
}

void VerificationWidget::on_enterBtn_clicked()
{
    password = ui->lineEdit->text();
    this->destroy();
    MainWindow* w = new MainWindow;
    w->show();
}

void VerificationWidget::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        ui->infoLabel->setText("Please input password with 16 character");
    }
    if(arg1.length() == 16)
    {
        ui->enterBtn->setEnabled(true);
    }
    else
    {
        ui->enterBtn->setEnabled(false);
    }
}

QString VerificationWidget::getPassword()
{
    return password;
}

#ifndef VERIFICATIONWIDGET_H
#define VERIFICATIONWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class VerificationWidget;
}

class VerificationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VerificationWidget(QWidget *parent = 0);
    ~VerificationWidget();

public:
    static QString getPassword();

    static bool isCanSave();
private:

    static QString password;

private slots:
    void on_enterBtn_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::VerificationWidget *ui;

    const char* _fillPassword = "fillPassword";
};

#endif // VERIFICATIONWIDGET_H

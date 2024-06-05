#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QString>

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QWidget
{
    Q_OBJECT    

public:
    explicit LoginScreen(QSqlDatabase* db,QWidget *parent = nullptr);
    ~LoginScreen();
signals:
    void SuccessLog();

private slots:
    void Log_In();
    void Registration ();
    void on_Button_Registration_clicked();
    void on_Button_Enter_clicked();

private:
    Ui::LoginScreen *ui;
    bool isLogIn;
    QSqlDatabase* db;
    QSqlQuery q;

};

#endif // LOGINSCREEN_H

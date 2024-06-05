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

    //Сигнат при успешной авторизации
    void SuccessLog();

private slots:

    //Проверка корректности заполененных полей и данных пользователя
    void Log_In();

    //Регистрация нового пользователя в базу данных
    void Registration ();

    //Переключение режимов регистрации и авторизации
    void on_Button_Registration_clicked();

    //Запуск проверки или регистрации
    void on_Button_Enter_clicked();

private:
    Ui::LoginScreen *ui;
    bool isLogIn;
    QSqlDatabase* db;
    QSqlQuery q;

};

#endif // LOGINSCREEN_H

#include "loginscreen.h"
#include "ui_loginscreen.h"
#include <QDebug>
#include <QTableView>
#include <QSqlTableModel>
#include <QPushButton>
#include <QRegularExpression>

LoginScreen::LoginScreen(QSqlDatabase* database,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);    
    isLogIn=true;
    ui->Edit_Password->setEchoMode(QLineEdit::Password);
    ui->Edit_Email->setMaxLength(20);
    ui->Edit_Password->setMaxLength(20);
    ui->Edit_Name->setVisible(false);
    ui->Label_Name->setVisible(false);
    db=database;
    q=QSqlQuery(*db);


}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::Log_In()
{

    QString email=ui->Edit_Email->text();
    QString password=ui->Edit_Password->text();

    //Проверка, что поля заполнены
    if (email==""||password=="")
    {
        ui->Label_Message->setText("Все поля должны быть заполнены");
        return;
    }
    //Поиск пользователя в базе данных и проверка пароля
    q.exec("SELECT password FROM users WHERE email=\'"+email+"\';");
    if (q.next())
    {
        if (q.value("password")==password)
        {
            ui->Edit_Email->clear();
            ui->Edit_Password->clear();
            emit SuccessLog();
        }
        else
        {
            ui->Label_Message->setText("Неправильная почта или пароль");
        }
    }
    else
    {
         ui->Label_Message->setText("Пользователь не найден");
    }

}

void LoginScreen::Registration(){
    QString email=ui->Edit_Email->text();
    QString login=ui->Edit_Name->text();
    QString password=ui->Edit_Password->text();

    //Проверка введенных значений через валидатор
    QRegularExpression regLogPass("[a-zA-Z0-9]{1,20}");
    QRegularExpression regEmail("^[A-Z0-9a-z._-]{1,}@(\\w+)(\\.(\\w+))(\\.(\\w+))?(\\.(\\w+))?$");
    QRegularExpressionValidator regLogPassVal(regLogPass);
    QRegularExpressionValidator regEmailVal(regEmail);

    int pos=0;
    if (regEmailVal.validate(email,pos)!=QValidator::Acceptable)
    {
        ui->Label_Message->setText("Неверно введеная почта");
        return;
    }
    if (regLogPassVal.validate(login,pos)!=QValidator::Acceptable)
    {
        ui->Label_Message->setText("Неверный символ в имени пользователя");
        return;
    }
    if (regLogPassVal.validate(password,pos)!=QValidator::Acceptable)
    {
        ui->Label_Message->setText("Неверный символ в пароле");
        return;
    }

    //Проверка на уникательность почты
    q.exec("SELECT login FROM users WHERE email=\'"+email+"\';");
    if (q.next())
    {
        ui->Label_Message->setText("Пользователь с такой почтой уже существует");
        return;
    }

    //Создание нового пользователя, если все проверки пройдены
    QString query("INSERT INTO users(login,password,email) VALUES(\'"+login+"\',\'"+password+"\',\'"+email+"\');");    
    q.exec(query);
    ui->Label_Message->setText("Пользователь успешно создан");
    ui->Edit_Email->clear();
    ui->Edit_Name->clear();
    ui->Edit_Password->clear();
}

void LoginScreen::on_Button_Registration_clicked()
{
    //Смена подписей у кнопок и лейблов в зависимоти от режима
    if (isLogIn)
    {
        ui->Button_Registration->setText("Авторизация");
        ui->Button_Enter->setText("Зарегистрироваться");
        ui->Label_Title->setText("Регистрация");
        ui->Edit_Name->setVisible(true);
        ui->Label_Name->setVisible(true);
    }
    else
    {
        ui->Button_Registration->setText("Регистрация");
        ui->Button_Enter->setText("Войти");
        ui->Label_Title->setText("Авторизация");
        ui->Edit_Name->setVisible(false);
        ui->Label_Name->setVisible(false);
    }
    ui->Edit_Email->clear();
    ui->Edit_Name->clear();
    ui->Edit_Password->clear();
    isLogIn=!isLogIn;
}

void LoginScreen::on_Button_Enter_clicked()
{
    if (isLogIn)
        Log_In();
    else
        Registration();
}


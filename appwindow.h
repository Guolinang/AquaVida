#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "loginscreen.h"
#include "databasemanager.h"
#include <QSqlDatabase>

namespace Ui {
class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = nullptr);
    ~AppWindow();

private slots:
    void swapWindow();

    void backLog();

private:
    Ui::AppWindow *ui;
    LoginScreen* logIn;
    DataBaseManager* manager;
    QStackedWidget stackWindow;
    QSqlDatabase db;

};

#endif // APPWINDOW_H

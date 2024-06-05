#include "appwindow.h"
#include "ui_appwindow.h"
#include <QVBoxLayout>

AppWindow::AppWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppWindow)
{
    ui->setupUi(this);  
    db=QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("123");
    db.setDatabaseName("Aqua");
    if (!db.open())
    {
        qDebug()<<db.lastError();
    }
    logIn=new LoginScreen(&db,this);
    manager=new DataBaseManager(&db,this);
    stackWindow.addWidget(logIn);
    stackWindow.addWidget(manager);
    ui->verticalLayout->addWidget(&stackWindow);
    connect(logIn,SIGNAL(SuccessLog()),this,SLOT(swapWindow()));
    connect(manager,SIGNAL(Exit()),this,SLOT(backLog()));
    this->setWindowTitle("AquaVida");
    this->setWindowIcon(QIcon(":/res/water.png"));
}

AppWindow::~AppWindow()
{
    db.close();
    delete ui;
}

void AppWindow::swapWindow()
{
    stackWindow.setCurrentWidget(manager);
}

void AppWindow::backLog()
{
    stackWindow.setCurrentWidget(logIn);
}

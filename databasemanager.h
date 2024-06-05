#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QWidget>
#include <QSqlDatabase>
#include "filter.h"
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QFile>
#include <QTableWidgetItem>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class DataBaseManager;
}

class DataBaseManager : public QWidget
{
    Q_OBJECT

public:

    explicit DataBaseManager(QSqlDatabase* database, QWidget *parent = nullptr);
    ~DataBaseManager();

private slots:

    //Смена таблицы на заказы
    void on_Button_Order_clicked();

    //Смена таблицы на клиентов
    void on_Button_Client_clicked();

    //Смена таблицы на продукцию
    void on_Button_Product_clicked();

    //Сохранение измений таблицы при редактировании
    void on_Button_Save_clicked();

    //Отмена изменений
    void on_Button_Cancel_clicked();

    //Вызов окна фильтрации
    void on_Button_Filter_clicked();

    //Вызов окна создания
    void on_Button_Insert_clicked();

    //Слот, принимающий значения после формы фильтрации
    void slotFilter(QList<QVariant> *list);

     //Слот, принимающий значения после формы создания
    void slotCreate(QList<QVariant> *list);

    //Печать отччета по выбранной таблицы
    void on_Button_Report_clicked();

    //Получение индукса выбранной ячейки
    void on_Table_clicked(const QModelIndex& index_);

    //Удаление элементов таблицы
    void on_Button_Delete_clicked();

    //Выход из учетной записи
    void on_Button_Exit_clicked();

private:

    //Установка внешних ключей
    void setRelation();

    //Заполения словарей для перевода названий и внешних ключей
    void initDictionary();

    //Перевод заголовков по словарю
    void translateHeaders(QString name);

    //Непосредственный вызов окна фильтрации/создания
    void initForm(int b);

    //Отчёт по клиентам
    void reportClient();

    //Отчёт по продуктам
    void reportProduct();

    //Отчёт по заказам
    void reportOrder();

signals:

    //Выход из учетной записи
    void Exit();

private:

    Ui::DataBaseManager *ui;


    QSqlDatabase* db;
    QSqlRelationalTableModel* dbModel;
    QMap<QString,QString> dictionary;
    QMap<QString,QString> tableFields;
    QMap<QString,QPair<QString,QString>> redactors;
    Filter* filter;
    QModelIndex curRow;
};

#endif // DATABASEMANAGER_H

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

    void on_Button_Order_clicked();

    void on_Button_Filter_clicked();

    void on_Button_Client_clicked();

    void on_Button_Product_clicked();

    void on_Button_Save_clicked();

    void on_Button_Cancel_clicked();

    void on_Button_Insert_clicked();

    void slotFilter(QList<QVariant> *list);

    void slotCreate(QList<QVariant> *list);

    void on_Button_Report_clicked();

    void on_Table_clicked(const QModelIndex& index_);

    void on_Button_Delete_clicked();

    void on_Button_Exit_clicked();

private:

    void setRelation();

    void initDictionary();

    void translateHeaders(QString name);

    void initForm(int b);

    void reportClient();

    void reportProduct();

    void reportOrder();

signals:
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

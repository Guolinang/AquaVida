#include "databasemanager.h"
#include "ui_databasemanager.h"
#include <QDebug>
#include <QSqlRelation>
#include <QSqlRecord>
#include <QSqlField>
#include <QMetaType>
#include <QVector>
#include <QPair>



DataBaseManager::DataBaseManager(QSqlDatabase* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataBaseManager)
{
    ui->setupUi(this);
    db=database;
    dbModel=new QSqlRelationalTableModel(this,*db);
    ui->Table->setItemDelegate(new QSqlRelationalDelegate(ui->Table));
    ui->Table->setModel(dbModel);
    ui->Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    initDictionary();
    on_Button_Order_clicked();
    dbModel->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
    dbModel->sort(0,Qt::AscendingOrder);

}

DataBaseManager::~DataBaseManager()
{
    delete ui;
}


void DataBaseManager::initDictionary()
{
    //Первое поле - названиеТаблицы_названиеСтолбца
    //Второе поле - русский перевод подписи столбца
    dictionary.insert("orders_clients_name_2","Клиент");
    dictionary.insert("orders_name","Продукт");
    dictionary.insert("orders_quantity","Количество");
    dictionary.insert("orders_date","Дата доставки");
    dictionary.insert("orders_order_status_status_2","Статус заказа");
    dictionary.insert("orders_status","Статус доставки");
    dictionary.insert("orders_deliveryman","Доставщик");
    dictionary.insert("products_name","Название");
    dictionary.insert("products_description","Описание");
    dictionary.insert("products_price","Цена");
    dictionary.insert("clients_name","Имя");
    dictionary.insert("clients_phone","Номер телефона");
    dictionary.insert("clients_email","Почта");
    dictionary.insert("clients_address","Адрес");

    //Первое поле - названиеТаблицы_названиеСтолбца
    //Второе поле -  если внешний ключ: (НазваниеТаблицы, ПолеВНей), иначе ("",ТипРедактора)
    redactors.insert("orders_clients_name_2",QPair("clients","name"));
    redactors.insert("orders_name",QPair("products","name"));
    redactors.insert("orders_quantity",QPair("","SpinBox"));
    redactors.insert("orders_date",QPair("","DateEdit"));
    redactors.insert("orders_order_status_status_2",QPair("order_status","status"));
    redactors.insert("orders_status",QPair("delivery_status","status"));
    redactors.insert("orders_deliveryman",QPair("","LineEdit"));
    redactors.insert("products_name",QPair("","LineEdit"));
    redactors.insert("products_description",QPair("","LineEdit"));
    redactors.insert("products_price",QPair("","SpinBox"));
    redactors.insert("clients_name",QPair("","LineEdit"));
    redactors.insert("clients_phone",QPair("","LineEdit"));
    redactors.insert("clients_email",QPair("","LineEdit"));
    redactors.insert("clients_address",QPair("","LineEdit"));

}


void DataBaseManager::translateHeaders(QString name)
{
    QSqlRecord header=dbModel->record();
    for (int i = 1; i < header.count(); ++i) {
        dbModel->setHeaderData(i,Qt::Orientation::Horizontal,dictionary[name+"_"+header.fieldName(i)]);
    }
}

void DataBaseManager::on_Button_Order_clicked()
{
    dbModel->setTable("orders");
    setRelation();
    dbModel->select();
    ui->Table->setColumnHidden(0,true);
    translateHeaders("orders");
}

void DataBaseManager::setRelation()
{
    dbModel->setRelation(1,QSqlRelation("clients","id","name"));
    dbModel->setRelation(2,QSqlRelation("products","id","name"));
    dbModel->setRelation(5,QSqlRelation("order_status","id","status"));
    dbModel->setRelation(6,QSqlRelation("delivery_status","id","status"));
}

void DataBaseManager::on_Button_Client_clicked()
{
    dbModel->setTable("clients");
    dbModel->select();
    ui->Table->setColumnHidden(0,true);
     translateHeaders("clients");
}

void DataBaseManager::on_Button_Product_clicked()
{
    dbModel->setTable("products");
    dbModel->select();
    ui->Table->setColumnHidden(0,true);
    translateHeaders("products");
}

void DataBaseManager::on_Button_Save_clicked()
{
    dbModel->submitAll();
    dbModel->sort(0,Qt::AscendingOrder);

}

void DataBaseManager::on_Button_Cancel_clicked()
{
    dbModel->setFilter("");
    dbModel->revertAll();
}

void DataBaseManager::initForm(int b){

    QSqlQuery query(*db);
    QList<QVector<QString>> listVec;
    QSqlRecord header=dbModel->record();
    QVector<QString> vector;
    QPair<QString,QString> pair;

    //В зависимости от заголовков находим в redactors нужный редактор
    //Или данные для поиска значений внешнего ключа для комбобокса
    //vector хранит в себе [НазваниеВнешнейТаблицы, НазваниеСтолбца, НазваниеТекущейКолонкиТекущейТаблицы ] для внешних ключей
    //или ["",ТипРедактора, НазваниеТекущейКолонкиТекущейТаблицы] для остальных
    for (int i = 1; i < header.count(); ++i) {
        pair=redactors[dbModel->tableName()+"_"+header.fieldName(i)];
        vector.push_back(pair.first);
        vector.push_back(pair.second);
        vector.push_back(dbModel->headerData(i,Qt::Horizontal).toString());
        listVec.push_back(vector);
        vector.clear();
    }    
    filter=new Filter(b,query,listVec);    
    connect(filter,SIGNAL(filterA(QList<QVariant>*)),this,SLOT(slotFilter(QList<QVariant>*)));
    connect(filter,SIGNAL(createA(QList<QVariant>*)),this,SLOT(slotCreate(QList<QVariant>*)));
    filter->exec();
    dbModel->sort(0,Qt::AscendingOrder);
    delete filter;
}

void DataBaseManager::on_Button_Filter_clicked()
{

    initForm(0);
}

void DataBaseManager::on_Button_Insert_clicked()
{
    initForm(1);
}

void DataBaseManager::slotCreate(QList<QVariant> *list)
{
    QSqlQuery q(*db);
    QString query="insert into " + dbModel->tableName();
    int size=list->size();
    if (dbModel->tableName()=="clients")
    {
        query+="(name,phone,email,address) values(";        

    }
    if (dbModel->tableName()=="products")
    {
        query+="(name,description,price) values(";

    }
    if (dbModel->tableName()=="orders")
    {
        query+="(client,product,quantity, date, order_status, delivery_status,deliveryman) values(";
        size=7;
    }
    for (int i=0;i<size;++i)
    {
       if (dbModel->tableName()=="orders"&&i==4)
        {query+="\'4\',";continue;}
       if (dbModel->tableName()=="orders"&&i==5)
        {query+="\'3\',";continue;}

       if (i<5)
        {query+="\'"+list->at(i).toString() +"\',";}
       else
         {query+="\'"+list->at(i-2).toString() +"\',";}
    } 
    query[query.size()-1]=')';
    query+=";";   
    q.exec(query);
    dbModel->select();
}

void DataBaseManager::slotFilter(QList<QVariant> *list){

    QString filterTable;
    QSqlRecord header=dbModel->record();
    for (int i=0;i<list->size();++i)
    {
        if (list->at(i).toString()=="")
        {
            continue;
        }
        if (dbModel->tableName()=="orders")
        {
            if (header.fieldName(i+1)=="clients_name_2")
            {
                filterTable+="client=\'";
            }
            else if (header.fieldName(i+1)=="order_status_status_2")
            {
                filterTable+="order_status=\'";
            }
            else if (header.fieldName(i+1)=="name")
            {
                filterTable+="product=\'";
            }
            else if (header.fieldName(i+1)=="status")
            {
                filterTable+="delivery_status=\'";
            }
            else
            {
                filterTable+=header.fieldName(i+1)+"=\'";
            }
        }
        else
        {
            filterTable+=header.fieldName(i+1)+"=\'";
        }
        filterTable+=list->at(i).toString()+"\' AND ";
    }
    filterTable.chop(4);

    dbModel->setFilter(filterTable);
}

void DataBaseManager::on_Button_Report_clicked()
{
    if ( dbModel->tableName()=="clients")
        reportClient();
    else if (dbModel->tableName()=="products")
        reportProduct();
    else
       reportOrder();
}

void DataBaseManager::reportClient()
{
    //Генерация отчета в формате html по клиентам
    QString doc;
    doc="<!DOCTYPE HTML>\n"
        "<html>"
            "<head>\n"
                 "<meta charset=\"utf-8\">\n"
            "</head>"
            "<body>\n"
                "<h2 style=\"text-align:center\">Отчёт по клиентам</h2>"
            "<table style=\"width: 100%;\">\n";
    QSqlQuery clients(*db);
    QSqlQuery tmp(*db);
    clients.exec("SELECT DISTINCT id,name from clients;");
    doc+="<tr>\n"
            "<th style=\"padding: 10px; text-align:center; font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561;\">"
                "Имя клиента "
            "</th>"
            "<th style=\"padding: 10px; text-align:center;font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561\">"
                "Количество заказов "
            "</th>"
            "<th style=\"padding: 10px; text-align:center;font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561\">"
                "Любимый продукт "
            "</th>"
          "</tr>";
    while (clients.next())
    {
        doc+="<tr>\n";
        doc+="<td style=\"padding: 10px; text-align:center;font-size: 14px; line-height: 20px border-top: 1px solid #716561;\" >\n"+ clients.value(1).toString()+"</td>\n";
        doc+="<td style=\"padding: 10px; text-align:center;font-size: 14px; line-height: 20px border-top: 1px solid #716561;\">\n";
        tmp.exec("SELECT COUNT(*) from orders WHERE client=\'"+clients.value(0).toString()+"\';");
        tmp.next();
        doc+=tmp.value(0).toString();
        doc+="</td>\n";
        tmp.exec("WITH tmp AS(SELECT client,product,sum(quantity)as qua FROM orders GROUP BY client, product ) SELECT products.name FROM tmp INNER JOIN products ON products.id=tmp.product WHERE client=" +clients.value(0).toString()+ " ORDER BY qua DESC LIMIT 1;");
        tmp.next();
        doc+="<td style=\"padding: 10px; text-align:center; 14px; line-height: 20px border-top: 1px solid #716561;\">\n";
            doc+=tmp.value(0).toString()+
            "</td>\n";
        doc+="</tr>\n";
    }

    doc+=   "</body\n>"
        "</html>";
    QFile text("IndexClient.html");
    text.open(QIODeviceBase::WriteOnly);
    text.write(doc.toUtf8());
    text.close();
    QDesktopServices::openUrl(QUrl("IndexClient.html"));
}

void DataBaseManager::reportProduct()
{
     //Генерация отчета в формате html по продуктам
    QString doc;
    doc="<!DOCTYPE HTML>\n"
        "<html>"
            "<head>\n"
                 "<meta charset=\"utf-8\">\n"
            "</head>"
            "<body>\n"
                "<h2 style=\"text-align:center\">Отчёт по продукции AquaVida</h2>"
            "<table style=\"width: 100%;\">\n";
    QSqlQuery products(*db);
    QSqlQuery tmp(*db);
    products.exec("SELECT DISTINCT id,name,price from products;");
    doc+="<tr>\n"
            "<th style=\"padding: 10px; text-align:center; font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561;\">"
                "Наименование товара "
            "</th>"
            "<th style=\"padding: 10px; text-align:center;font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561\">"
                "Цена"
            "</th>"
               "<th style=\"padding: 10px; text-align:center;font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561\">"
                "Количество проданных"
            "</th>"
            "<th style=\"padding: 10px; text-align:center;font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561\">"
                "Принесенный доход"
            "</th>"
          "</tr>";
    while (products.next())
    {
        doc+="<tr>\n";
        doc+="<td style=\"padding: 10px; text-align:center;font-size: 14px; line-height: 20px border-top: 1px solid #716561;\" >\n"+ products.value(1).toString()+"</td>\n";
        doc+="<td style=\"padding: 10px; text-align:center;font-size: 14px; line-height: 20px border-top: 1px solid #716561;\">\n";

        tmp.exec("SELECT price from products where id=\'"+products.value(0).toString()+"\';");
        tmp.next();
        doc+=tmp.value(0).toString();
        doc+="</td>\n";
        doc+="<td style=\"padding: 10px; text-align:center; 14px; line-height: 20px border-top: 1px solid #716561;\">\n";
        tmp.exec("SELECT sum(quantity) FROM orders  WHERE product="+products.value(0).toString() +" GROUP BY product;");
        tmp.next();
        doc+=tmp.value(0).toString()+"</td>\n";

        doc+="<td style=\"padding: 10px; text-align:center; 14px; line-height: 20px border-top: 1px solid #716561;\">\n";
        tmp.exec("WITH sum AS(select sum(orders.quantity) AS su, orders.product FROM orders JOIN products ON orders.product = products.id GROUP BY orders.product) SELECT products.price*sum.su FROM products JOIN sum ON sum.product=products.id WHERE products.id=\'"+products.value(0).toString()+"\';");
        tmp.next();
        doc+=tmp.value(0).toString()+" ₽</td>\n";
        doc+="</tr>\n";
    }

    doc+=   "</body\n>"
        "</html>";
    QFile text("IndexProduct.html");
    text.open(QIODeviceBase::WriteOnly);
    text.write(doc.toUtf8());
    text.close();
     QDesktopServices::openUrl(QUrl("IndexProduct.html"));
}

void DataBaseManager::reportOrder()
{
    //Генерация отчета в формате html по заказам
    QString doc;
    doc="<!DOCTYPE HTML>\n"
        "<html>"
            "<head>\n"
                 "<meta charset=\"utf-8\">\n"
            "</head>"
            "<body>\n"
                "<h2 style=\"text-align:center\">Отчёт по доставкам AquaVida</h2>"
            "<table style=\"width: 100%;\">\n";
    QSqlQuery orders(*db);
    QSqlQuery tmp(*db);
    orders.exec("SELECT id,client,deliveryman,date,order_status from orders;");
    tmp.exec("SELECT count(*) FROM orders;");
    tmp.next();
    int count=tmp.value(0).toInt();
    doc+="<h4>Общее число доставок:"+tmp.value(0).toString() +"</h4>";
    doc+="<tr>\n"
            "<th style=\"padding: 10px; text-align:center; font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561;\">"
                "Клиент"
            "</th>"
            "<th style=\"padding: 10px; text-align:center;font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561\">"
                "Доставщик"
            "</th>"
               "<th style=\"padding: 10px; text-align:center;font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561\">"
                 "Дата доставки"
            "</th>"
            "<th style=\"padding: 10px; text-align:center;font-weight: 500;font-size: 16px;line-height: 20px;border-top: 2px solid #716561;border-bottom: 2px solid #716561\">"
                "Статус заказа"
            "</th>"
          "</tr>";
    while (orders.next())
    {
        doc+="<tr>\n";
            tmp.exec("SELECT name FROM orders  JOIN clients ON orders.client=clients.id WHERE orders.id=\'"+orders.value(0).toString()+"\';");
            tmp.next();
            doc+="<td style=\"padding: 10px; text-align:center; 14px; line-height: 20px border-top: 1px solid #716561;\"\n>"+tmp.value(0).toString()+"</td>\n";

            tmp.exec("SELECT deliveryman FROM orders  WHERE orders.id=\'"+orders.value(0).toString()+"\';");
            tmp.next();
            doc+="<td style=\"padding: 10px; text-align:center; 14px; line-height: 20px border-top: 1px solid #716561;\"\n>"+tmp.value(0).toString()+"</td>\n";

            tmp.exec("SELECT date FROM orders  WHERE orders.id=\'"+orders.value(0).toString()+"\';");
            tmp.next();
            doc+="<td style=\"padding: 10px; text-align:center; 14px; line-height: 20px border-top: 1px solid #716561;\"\n>"+tmp.value(0).toString()+"</td>\n";

            tmp.exec("SELECT order_status.status FROM orders JOIN order_status on orders.order_status=order_status.id WHERE orders.id=\'" +orders.value(0).toString()+"\';");
            tmp.next();
            doc+="<td style=\"padding: 10px; text-align:center; 14px; line-height: 20px border-top: 1px solid #716561;\"\n>" + tmp.value(0).toString() +"</td>\n";

        doc+="</tr>\n";
    }


    float temp;
    tmp.exec("SELECT count(*) from orders where order_status='1';");
    tmp.next();
    doc+="<h4> Статистика по доставкам:</h4>\n";

    tmp.exec("SELECT count(*) from orders where order_status='1';");
    tmp.next();
    temp=(tmp.value(0).toInt()*100/count);
    doc+="<h4> В процессе:"+QString::number(temp)+"%</h4>";


    tmp.exec("SELECT count(*) from orders where order_status='2';");
    tmp.next();
     temp=(tmp.value(0).toInt()*100/count);
    doc+="<h4> Доставлено:"+QString::number(temp)+"%</h4>";

    tmp.exec("SELECT count(*) from orders where order_status='3';");
    tmp.next();
     temp=(tmp.value(0).toInt()*100/count);
    doc+="<h4> Отменено:"+QString::number(temp)+"%</h4>";

    tmp.exec("SELECT count(*) from orders where order_status='4';");
    tmp.next();
     temp=(tmp.value(0).toInt()*100/count);
    doc+="<h4> В обработке:"+QString::number(temp)+"%</h4>";


    doc+=   "</body\n>"
        "</html>";
    QFile text("IndexOrder.html");
    text.open(QIODeviceBase::WriteOnly);
    text.write(doc.toUtf8());
    text.close();
    QDesktopServices::openUrl(QUrl("IndexOrder.html"));
}


void DataBaseManager::on_Table_clicked(const QModelIndex& index_)
{
    curRow=index_.sibling(index_.row(),0);

}

void DataBaseManager::on_Button_Delete_clicked()
{
    QSqlQuery q(*db);
    QString s = dbModel->data(curRow).toString();
    QString str="DELETE FROM "+ dbModel->tableName()+" WHERE id=\'"+ s  +"\'";
    q.exec(str);
    on_Button_Save_clicked();
}


void DataBaseManager::on_Button_Exit_clicked()
{
    emit Exit();
}


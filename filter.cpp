#include "filter.h"
#include "ui_filter.h"


Filter::Filter(int isC, QSqlQuery & query,QList<QVector<QString>>& redactors,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filter)
{
    ui->setupUi(this);
    isCreate=isC;
    QWidget* widget;
    header=new QLabel;
    header->setStyleSheet("font-weight:bold;font-size: 15px;");
    if (isC)
       {header->setText("Заполните поля для создания"); ui->Button_CF->setText("Создать");}
    else
       {header->setText("Выберите поля для фильтрации и заполните их");ui->Button_CF->setText("Отфильтровать");}
    ui->Layot_V->addWidget(header);
    QWidget* name;
    qDebug()<<redactors;
    for (auto &it:redactors)
    {
        if (it[0]=="")
        {

            if (it[1]=="SpinBox")
            {
              widget=new QSpinBox(this);
              qobject_cast<QSpinBox*>(widget)->setMaximum(INT_MAX);
              qobject_cast<QSpinBox*>(widget)->setMinimum(1);
            }
            else if (it[1]=="LineEdit")
            {
                widget=new QLineEdit(this);
                if (it[2]=="Номер телефона")
                 {
                    qobject_cast<QLineEdit*>(widget)->setValidator( new QRegularExpressionValidator(QRegularExpression("^\\d{1,2}\\d{3,5}\\d{2,7}$"),this)); }
            }
            else if (it[1]=="DateEdit")
            {
                widget=new QDateEdit(this);
                qobject_cast<QDateEdit*>(widget)->setDate(QDate::currentDate());
                qobject_cast<QDateEdit*>(widget)->setMinimumDate(QDate::currentDate());
            }

        }
        else
        {
            if (it[1]=="status"&&isC==1)
                continue;
            query.exec("SELECT DISTINCT "+it[1]+",id"  +" FROM "+ it[0]+";");
            widget=new QComboBox(this);
            while (query.next())
            {
                qobject_cast<QComboBox*>(widget)->addItem(query.value(0).toString(),query.value(1).toString());
            }

        }
        if (isC)
            name=new QLabel(it[2],this);
        else
            name=new QCheckBox(it[2],this);
        ui->Layot_V->addWidget(name);
        ui->Layot_V->addWidget(widget);
    }
    this->setWindowTitle("AquaVida");
    this->setWindowIcon(QIcon(":/res/water.png"));


}

Filter::~Filter()
{
    delete ui;
}


void Filter::on_Button_CF_clicked()
{
    QVariant value;
    QList<QVariant>* list=new QList<QVariant>;
    if (!isCreate)
    {

        for (int i=2;i<ui->Layot_V->count();i=i+2 )
        {
            if ( qobject_cast<QCheckBox*>(ui->Layot_V->itemAt(i-1)->widget())->isChecked())
            {
                if (qobject_cast<QLineEdit*>(ui->Layot_V->itemAt(i)->widget()))
                {                
                  value = qobject_cast<QLineEdit*>(ui->Layot_V->itemAt(i)->widget())->text();
                }
                else if (qobject_cast<QComboBox*>(ui->Layot_V->itemAt(i)->widget()))
                {
                  value = qobject_cast<QComboBox*>(ui->Layot_V->itemAt(i)->widget())->currentData();
                }
                else if (qobject_cast<QDateEdit*>(ui->Layot_V->itemAt(i)->widget()))
                {
                  value = qobject_cast<QDateEdit*>(ui->Layot_V->itemAt(i)->widget())->date();
                }
                else if (qobject_cast<QSpinBox*>(ui->Layot_V->itemAt(i)->widget()))
                {
                  value = qobject_cast<QSpinBox*>(ui->Layot_V->itemAt(i)->widget())->value();
                }
            }
            else
                value = "";
            list->push_back(value);
        }
        emit filterA(list);
    }
    else
    {
        for (int i=2;i<ui->Layot_V->count();i=i+2 )
        {
            if (qobject_cast<QLineEdit*>(ui->Layot_V->itemAt(i)->widget()))
            {
                if (qobject_cast<QLineEdit*>(ui->Layot_V->itemAt(i)->widget())->text().size()==0)
                {
                    header->setText("Заполните все поля");
                    return;
                }
              value = qobject_cast<QLineEdit*>(ui->Layot_V->itemAt(i)->widget())->text();
            }
            else if (qobject_cast<QComboBox*>(ui->Layot_V->itemAt(i)->widget()))
            {
              value = qobject_cast<QComboBox*>(ui->Layot_V->itemAt(i)->widget())->currentData();
            }
            else if (qobject_cast<QDateEdit*>(ui->Layot_V->itemAt(i)->widget()))
            {
              value = qobject_cast<QDateEdit*>(ui->Layot_V->itemAt(i)->widget())->date();
            }
            else if (qobject_cast<QSpinBox*>(ui->Layot_V->itemAt(i)->widget()))
            {
              value = qobject_cast<QSpinBox*>(ui->Layot_V->itemAt(i)->widget())->value();
            }
            list->push_back(value);
        }
        emit createA(list);
    }
    this->close();
}




void Filter::on_Button_Cancel_clicked()
{
    this->close();
}


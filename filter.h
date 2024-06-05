#ifndef FILTER_H
#define FILTER_H

#include <QDialog>
#include <QTableView>
#include <QSqlQuery>
#include <QItemDelegate>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QDateEdit>
#include <QSortFilterProxyModel>
namespace Ui {
class Filter;
}

class Filter : public QDialog
{
    Q_OBJECT

public:
    explicit Filter(int isCreate,QSqlQuery & query,QList<QVector<QString>>& redactors, QWidget *parent = nullptr);
    ~Filter();
private slots:
    void on_Button_CF_clicked();

    void on_Button_Cancel_clicked();

signals:

    void filterA(QList<QVariant>* list);
    void createA(QList<QVariant>* list);


private:
    Ui::Filter *ui;
    bool isCreate;
    QLabel* header;


};

#endif // FILTER_H

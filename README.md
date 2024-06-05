# AquaVida

### Описание

Приложение, позволяющее сотрудникам компании AquaVida управлять доставками, заказами, регистрировать новых клиентов и товары, а также составлять отчёты.

### Установка

Для корректной работы приложения необходимо, чтобы на устройстве был установлен [postgreSQL](https://www.postgresql.org/).
После установки postgreSQL необходимо создать базу данных Aqua и запустить скрипт Aqua.sql. Создайте пользователя Aqua с паролем "123".
Для этого введите в консоль следующие команды:

```Bash
chcp 1252
psql -U postgres
```

Далее введите пароль пользователя postgres. Создайте нового пользователя Aqua

```Bash
CREATE USER aqua WITH PASSWORD '123';
CREATE DATABASE aqua;
```

Дать права доступа на чтение и запись пользователю aqua от имени postgres и запустить скрипт

```Bash
\c aqua
GRANT ALL PRIVILEGIES ON DATABASE aqua TO aqua;
GRANT pg_read_all_data TO aqua;
GRANT pg_write_all_data TO aqua;
\i postgresql/Aqua.sql

```

После этого можно запустить исполняемый файл AquaVida.exe или собрать приложение из исходников

### Описание функционала

При запуске пользователя встречает экран авторизации, на котором можно как войти по уже существующим данным, так и зарегистрироваться с указанием почты, имени и пароля.
Основное окно представляет собой таблицу и интерфейс взаимодействия с ней.

Пользователю доступны следующие функции:

- Просмотр
- Фильтрация
- Добавление новых элементов
- Удаление записей
- Редактирование таблицы
- Генерация отчета по выбранной таблице

Смена таблиц осуществляется при помощи кнопок в левой части окна приложения. Генерация отчёта выполняется в формате html по нажатию на соответсвующую кнопку. Готовый отчет открывается в браузере.
Приложение позволяет управлять табллицами содержащими данные о **клиентах**, **товарах** и **заказах**.

### Примеры и кейсы взаимодействия

Допустим, поступил заказ от нового клиента N, который хочет приобрести товар 'Вода без газа 0.5' в количестве 50ти штук . В таком случае менеджер компании AquaVida заносит нового клиента в базу клиентов, заполняя актуальную контактную информацию и адрес доставки. После этого менеджер создает новый заказ в таблице заказов на имя N товара 'Вода без газа 0.5' в количестве 50ти штук и назначает доставку определенному доставщику.

### Скриншоты интерфейса приложения

![Экран авторизации](/images/LogIn.png)

Экран авторизации

![Главное окно](/images/MainWindow.png)

Главное окно

![Добавление нового](/images/AddNew.png)

Добавление новой записи

![Фильтрация](/images/Filter.png)

Фильтрация

![Отчёт по клиентам](/images/ReportClients.png)

Отчёт по клиентам

![Отчёт по товарам](/images/ReportProducts.png)

Отчёт по товарам

![Отчёт по заказам](/images/ReportOrders.png)

Отчёт по заказам

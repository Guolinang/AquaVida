-- SQL Manager for PostgreSQL 6.5.1.57809
-- ---------------------------------------
-- Хост         : localhost
-- База данных  : Aqua
-- Версия       : PostgreSQL 16.3, compiled by Visual C++ build 1938, 64-bit



SET check_function_bodies = false;
--
-- Structure for table clients (OID = 16575) : 
--
SET search_path = public, pg_catalog;
CREATE TABLE public.clients (
    id bigserial NOT NULL,
    name varchar(255) NOT NULL,
    phone varchar(20) NOT NULL,
    email varchar(255) NOT NULL,
    address varchar(255) NOT NULL
)
WITH (oids = false);
--
-- Structure for table users (OID = 16621) : 
--
CREATE TABLE public.users (
    id bigserial NOT NULL,
    login varchar(20) NOT NULL,
    password varchar(20) NOT NULL,
    email varchar(255) NOT NULL
)
WITH (oids = false);
--
-- Structure for table products (OID = 16642) : 
--
CREATE TABLE public.products (
    id bigserial NOT NULL,
    name varchar(255) NOT NULL,
    description text NOT NULL,
    price real NOT NULL
)
WITH (oids = false);
ALTER TABLE ONLY public.products ALTER COLUMN price SET STATISTICS 0;
--
-- Structure for table orders (OID = 16660) : 
--

CREATE TABLE public.delivery_status (
    id bigserial NOT NULL,
    status varchar(50) NOT NULL
)
WITH (oids = false);
ALTER TABLE ONLY public.delivery_status ALTER COLUMN status SET STATISTICS 0;
--
-- Structure for table order_status (OID = 16686) : 
--
CREATE TABLE public.order_status (
    id bigserial NOT NULL,
    status varchar(50) NOT NULL
)
WITH (oids = false);
ALTER TABLE ONLY public.order_status ALTER COLUMN id SET STATISTICS 0;
ALTER TABLE ONLY public.order_status ALTER COLUMN status SET STATISTICS 0;

CREATE TABLE public.orders (
    id bigserial NOT NULL,
    client bigint NOT NULL,
    product bigint NOT NULL,
    quantity integer NOT NULL,
    date date NOT NULL,
    order_status integer NOT NULL,
    delivery_status integer NOT NULL,
    deliveryman varchar(255) NOT NULL
)
WITH (oids = false);
ALTER TABLE ONLY public.orders ALTER COLUMN quantity SET STATISTICS 0;
ALTER TABLE ONLY public.orders ALTER COLUMN date SET STATISTICS 0;
ALTER TABLE ONLY public.orders ALTER COLUMN order_status SET STATISTICS 0;
ALTER TABLE ONLY public.orders ALTER COLUMN delivery_status SET STATISTICS 0;
ALTER TABLE ONLY public.orders ALTER COLUMN deliveryman SET STATISTICS 0;
--
-- Structure for table delivery_status (OID = 16677) : 
--

--
-- Data for table public.clients (OID = 16575) (LIMIT 0,5)
--
INSERT INTO public.clients (id, name, phone, email, address) OVERRIDING SYSTEM VALUE
VALUES (2, 'Дмитрий', '761020', 'kjhbk@mail.ru', 'Лондон');

INSERT INTO public.clients (id, name, phone, email, address) OVERRIDING SYSTEM VALUE
VALUES (3, 'Мария', '334234', 'afadsk@mail.ru', 'Москва');

INSERT INTO public.clients (id, name, phone, email, address) OVERRIDING SYSTEM VALUE
VALUES (1, 'Анна', '1213423452', 'bk@mail.ru', 'Тверь');

INSERT INTO public.clients (id, name, phone, email, address) OVERRIDING SYSTEM VALUE
VALUES (4, 'Егор', '1231254', 'bob@mail.ru', 'Екатеринбур');

INSERT INTO public.clients (id, name, phone, email, address) OVERRIDING SYSTEM VALUE
VALUES (5, 'Константин', '24124', 'b213k@mail.ru', 'Зеленоград');

--
-- Data for table public.users (OID = 16621) (LIMIT 0,6)
--
INSERT INTO public.users (id, login, password, email) OVERRIDING SYSTEM VALUE
VALUES (8, 'admin', 'admin', 'admin@mail.ru');

INSERT INTO public.users (id, login, password, email) OVERRIDING SYSTEM VALUE
VALUES (10, 'ad', 'min', 'admin@mail.com');

INSERT INTO public.users (id, login, password, email) OVERRIDING SYSTEM VALUE
VALUES (11, 'ad', 'min', 'admin@mail.kz');

INSERT INTO public.users (id, login, password, email) OVERRIDING SYSTEM VALUE
VALUES (12, '123', 'amru', 'a@m.ru');

INSERT INTO public.users (id, login, password, email) OVERRIDING SYSTEM VALUE
VALUES (13, 'admin', 'admin', 'admin@admin.com');

INSERT INTO public.users (id, login, password, email) OVERRIDING SYSTEM VALUE
VALUES (14, 'ad', 'min', 'Ad@mail.ru');

--
-- Data for table public.products (OID = 16642) (LIMIT 0,5)
--
INSERT INTO public.products (id, name, description, price) OVERRIDING SYSTEM VALUE
VALUES (1, 'Вода 0.5л', '0.5 л чистой воды', 25);

INSERT INTO public.products (id, name, description, price) OVERRIDING SYSTEM VALUE
VALUES (3, 'Вода 1л', '1л воды', 220);

INSERT INTO public.products (id, name, description, price) OVERRIDING SYSTEM VALUE
VALUES (4, 'Фанта 1л', '1л фанты', 100);

INSERT INTO public.products (id, name, description, price) OVERRIDING SYSTEM VALUE
VALUES (2, 'Кола 1л', '1л газировки', 100);

INSERT INTO public.products (id, name, description, price) OVERRIDING SYSTEM VALUE
VALUES (6, 'Спрайт', 'Бутылка спрайта', 190);

--
-- Data for table public.orders (OID = 16660) (LIMIT 0,8)
--
INSERT INTO public.orders (id, client, product, quantity, date, order_status, delivery_status, deliveryman) OVERRIDING SYSTEM VALUE
VALUES (8, 2, 2, 1, '2012-12-10', 2, 1, 'Максим');

INSERT INTO public.orders (id, client, product, quantity, date, order_status, delivery_status, deliveryman) OVERRIDING SYSTEM VALUE
VALUES (5, 2, 2, 1, '2012-12-10', 2, 1, 'Максим');

INSERT INTO public.orders (id, client, product, quantity, date, order_status, delivery_status, deliveryman) OVERRIDING SYSTEM VALUE
VALUES (10, 1, 1, 10, '2024-06-06', 1, 1, 'Aлексей');

INSERT INTO public.orders (id, client, product, quantity, date, order_status, delivery_status, deliveryman) OVERRIDING SYSTEM VALUE
VALUES (4, 1, 1, 1, '2027-12-10', 1, 2, 'Максим');

INSERT INTO public.orders (id, client, product, quantity, date, order_status, delivery_status, deliveryman) OVERRIDING SYSTEM VALUE
VALUES (1, 1, 1, 1, '2027-12-10', 1, 2, 'Людмила');

INSERT INTO public.orders (id, client, product, quantity, date, order_status, delivery_status, deliveryman) OVERRIDING SYSTEM VALUE
VALUES (14, 2, 4, 10, '2031-06-04', 4, 3, 'Людмила');

INSERT INTO public.orders (id, client, product, quantity, date, order_status, delivery_status, deliveryman) OVERRIDING SYSTEM VALUE
VALUES (9, 3, 3, 1, '2012-12-10', 3, 3, 'Герман');

INSERT INTO public.orders (id, client, product, quantity, date, order_status, delivery_status, deliveryman) OVERRIDING SYSTEM VALUE
VALUES (17, 3, 6, 132, '2024-06-06', 4, 3, 'Егор');

--
-- Data for table public.delivery_status (OID = 16677) (LIMIT 0,4)
--
INSERT INTO public.delivery_status (id, status) OVERRIDING SYSTEM VALUE
VALUES (1, 'В пути');

INSERT INTO public.delivery_status (id, status) OVERRIDING SYSTEM VALUE
VALUES (2, 'Доставлен');

INSERT INTO public.delivery_status (id, status) OVERRIDING SYSTEM VALUE
VALUES (3, 'Не доставлено');

INSERT INTO public.delivery_status (id, status) OVERRIDING SYSTEM VALUE
VALUES (4, 'Отменен');

--
-- Data for table public.order_status (OID = 16686) (LIMIT 0,4)
--
INSERT INTO public.order_status (id, status) OVERRIDING SYSTEM VALUE
VALUES (1, 'В процессе');

INSERT INTO public.order_status (id, status) OVERRIDING SYSTEM VALUE
VALUES (2, 'Доставлен');

INSERT INTO public.order_status (id, status) OVERRIDING SYSTEM VALUE
VALUES (3, 'Отменён');

INSERT INTO public.order_status (id, status) OVERRIDING SYSTEM VALUE
VALUES (4, 'В обработке');

--
-- Definition for index clients_name_key (OID = 16587) : 
--
CREATE UNIQUE INDEX clients_name_key ON public.clients USING btree (name);
--
-- Definition for index clients_pkey (OID = 16581) : 
--
ALTER TABLE ONLY public.clients
    ADD CONSTRAINT clients_pkey
    PRIMARY KEY (id);
--
-- Definition for index clients_email_key (OID = 16583) : 
--
ALTER TABLE ONLY public.clients
    ADD CONSTRAINT clients_email_key
    UNIQUE (email);
--
-- Definition for index clients_phone_key (OID = 16585) : 
--
ALTER TABLE ONLY public.clients
    ADD CONSTRAINT clients_phone_key
    UNIQUE (phone);
--
-- Definition for index users_pkey (OID = 16625) : 
--
ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey
    PRIMARY KEY (id);
--
-- Definition for index users_email_key (OID = 16627) : 
--
ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_email_key
    UNIQUE (email);
--
-- Definition for index products_pkey (OID = 16646) : 
--
ALTER TABLE ONLY public.products
    ADD CONSTRAINT products_pkey
    PRIMARY KEY (id);
--
-- Definition for index products_name_key (OID = 16648) : 
--
ALTER TABLE ONLY public.products
    ADD CONSTRAINT products_name_key
    UNIQUE (name);
--
-- Definition for index orders_pkey1 (OID = 16664) : 
--
ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_pkey1
    PRIMARY KEY (id);
--
-- Definition for index delivery_status_pkey (OID = 16681) : 
--
ALTER TABLE ONLY public.delivery_status
    ADD CONSTRAINT delivery_status_pkey
    PRIMARY KEY (id);
--
-- Definition for index delivery_status_status_key (OID = 16683) : 
--
ALTER TABLE ONLY public.delivery_status
    ADD CONSTRAINT delivery_status_status_key
    UNIQUE (status);
--
-- Definition for index order_status_pkey (OID = 16690) : 
--
ALTER TABLE ONLY public.order_status
    ADD CONSTRAINT order_status_pkey
    PRIMARY KEY (id);
--
-- Definition for index order_status_status_key (OID = 16692) : 
--
ALTER TABLE ONLY public.order_status
    ADD CONSTRAINT order_status_status_key
    UNIQUE (status);
--
-- Definition for index orders_fk1 (OID = 16704) : 
--
ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_fk1
    FOREIGN KEY (product) REFERENCES products(id) ON UPDATE CASCADE ON DELETE CASCADE;
--
-- Definition for index orders_fk (OID = 16709) : 
--
ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_fk
    FOREIGN KEY (client) REFERENCES clients(id) ON UPDATE CASCADE ON DELETE CASCADE;
--
-- Definition for index orders_fk2 (OID = 16714) : 
--
ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_fk2
    FOREIGN KEY (delivery_status) REFERENCES delivery_status(id) ON UPDATE CASCADE ON DELETE CASCADE;
--
-- Definition for index orders_fk3 (OID = 16719) : 
--
ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_fk3
    FOREIGN KEY (order_status) REFERENCES order_status(id) ON UPDATE CASCADE ON DELETE CASCADE;
--
-- Data for sequence public.clients_id_seq (OID = 16574)
--
SELECT pg_catalog.setval('public.clients_id_seq', 5, true);
--
-- Data for sequence public.users_id_seq (OID = 16620)
--
SELECT pg_catalog.setval('public.users_id_seq', 14, true);
--
-- Data for sequence public.products_id_seq (OID = 16641)
--
SELECT pg_catalog.setval('public.products_id_seq', 6, true);
--
-- Data for sequence public.orders_id_seq1 (OID = 16659)
--
SELECT pg_catalog.setval('public.orders_id_seq', 17, true);
--
-- Data for sequence public.delivery_status_id_seq (OID = 16676)
--
SELECT pg_catalog.setval('public.delivery_status_id_seq', 4, true);
--
-- Data for sequence public.order_status_id_seq (OID = 16685)
--
SELECT pg_catalog.setval('public.order_status_id_seq', 10, true);
--
-- Comments
--
COMMENT ON SCHEMA public IS 'standard public schema';

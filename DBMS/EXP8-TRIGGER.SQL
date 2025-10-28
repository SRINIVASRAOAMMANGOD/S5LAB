-------------------Create Describe and Insert into table--------------------------

mysql> CREATE TABLE Item (
    -> item_id INT PRIMARY KEY, item_desc VARCHAR(30), qty_on_hand INT,
    -> unit_price INT, category VARCHAR(30));
Query OK, 0 rows affected (0.03 sec)

mysql> DESC Item;
+-------------+-------------+------+-----+---------+-------+ 
| Field       | Type        | Null | Key | Default | Extra |
+-------------+-------------+------+-----+---------+-------+
| item_id     | int         | NO   | PRI | NULL    |       |
| item_desc   | varchar(30) | YES  |     | NULL    |       |
| qty_on_hand | int         | YES  |     | NULL    |       |
| unit_price  | int         | YES  |     | NULL    |       |
| category    | varchar(30) | YES  |     | NULL    |       |
+-------------+-------------+------+-----+---------+-------+

mysql> INSERT INTO Item VALUES (100, 'TextBook', 20, 20, 'book'), (101, 'milkybar', 30, 5, 'chocolate'), (102, 'apple', 50, 10, 'fruit'), (103, 'pen', 100, 8, 'stationary');
Query OK, 4 rows affected (0.01 sec)
Records: 4  Duplicates: 0  Warnings: 0

mysql> SELECT * FROM Item;
+---------+-----------+-------------+------------+------------+
| item_id | item_desc | qty_on_hand | unit_price | category   |
+---------+-----------+-------------+------------+------------+
|     100 | TextBook  |          20 |         20 | book       |
|     101 | milkybar  |          30 |          5 | chocolate  |
|     102 | apple     |          50 |         10 | fruit      |
|     103 | pen       |         100 |          8 | stationary |
+---------+-----------+-------------+------------+------------+
4 rows in set (0.00 sec)

mysql> CREATE TABLE Sales (
    -> sale_id INT PRIMARY KEY, item_id INT, qty_sold INT, unit_price INT, 
    -> total_price INT, tax_amount DECIMAL(10,2), grand_total INT,
    -> FOREIGN KEY (item_id) REFERENCES Item(item_id) );
Query OK, 0 rows affected (0.05 sec)

mysql> DESC Sales;
+-------------+---------------+------+-----+---------+-------+
| Field       | Type          | Null | Key | Default | Extra |
+-------------+---------------+------+-----+---------+-------+
| sale_id     | int           | NO   | PRI | NULL    |       |
| item_id     | int           | YES  | MUL | NULL    |       |
| qty_sold    | int           | YES  |     | NULL    |       |
| unit_price  | int           | YES  |     | NULL    |       |
| total_price | int           | YES  |     | NULL    |       |
| tax_amount  | decimal(10,2) | YES  |     | NULL    |       |
| grand_total | int           | YES  |     | NULL    |       |
+-------------+---------------+------+-----+---------+-------+


---------------------------Question AND Query-------------------------------------------------

Q1: Create trigger for calculating total_price, tax_amount and grand_total in sales table while inserting values.
	The tax rate of vaious category as shown below.
        book (10%), stationery (20%), chocolate (30%), other (5%)

mysql> DELIMITER //
mysql> CREATE TRIGGER sale_entry BEFORE INSERT ON Sales FOR EACH ROW 
    -> BEGIN 
    -> DECLARE prod_cat VARCHAR(30); 
    -> DECLARE tax_rate DECIMAL(10,2); 
    -> SELECT category INTO prod_cat FROM Item WHERE item_id=new.item_id; 
    -> SET new.unit_price=(SELECT unit_price FROM Item WHERE item_id=new.item_id); 
    -> SET new.total_price=new.qty_sold*new.unit_price; 
    -> IF prod_cat='book' THEN 
    ->   SET tax_rate=0.10; 
    -> ELSEIF prod_cat='stationary' THEN 
    ->   SET tax_rate=0.20; 
    -> ELSEIF prod_cat='chocolate' THEN   
    ->   SET tax_rate=0.30; 
    -> ELSE  
    ->   SET tax_rate=0.05; 
    -> END IF; 
    -> SET new.tax_amount=new.total_price*tax_rate; 
    -> SET new.grand_total=new.total_price+new.tax_amount; 
    -> END//
Query OK, 0 rows affected (0.01 sec)


Q2: Create a trigger to calculate the stock of an Item after sales of an Item.

mysql> DELIMITER ;
mysql> CREATE TRIGGER upd_qty AFTER INSERT ON Sales FOR EACH ROW
    -> UPDATE Item SET qty_on_hand=qty_on_hand-new.qty_sold WHERE item_id=new.item_id;
Query OK, 0 rows affected (0.00 sec)


---------------------USE CASE----------------------------------------------------

mysql> SELECT * FROM Item;
+---------+-----------+-------------+------------+------------+
| item_id | item_desc | qty_on_hand | unit_price | category   |
+---------+-----------+-------------+------------+------------+
|     100 | TextBook  |          20 |         20 | book       |
|     101 | milkybar  |          30 |          5 | chocolate  |
|     102 | apple     |          50 |         10 | fruit      |
|     103 | pen       |         100 |          8 | stationary |
+---------+-----------+-------------+------------+------------+
4 rows in set (0.00 sec)

mysql> SELECT * FROM Sales;
Empty set (0.00 sec)

mysql> INSERT INTO Sales(sale_id,item_id,qty_sold) VALUES(200,100,10);
Query OK, 1 row affected (0.01 sec)

mysql> SELECT * FROM Item;
+---------+-----------+-------------+------------+------------+
| item_id | item_desc | qty_on_hand | unit_price | category   |
+---------+-----------+-------------+------------+------------+
|     100 | TextBook  |          10 |         20 | book       |
|     101 | milkybar  |          30 |          5 | chocolate  |
|     102 | apple     |          50 |         10 | fruit      |
|     103 | pen       |         100 |          8 | stationary |
+---------+-----------+-------------+------------+------------+
4 rows in set (0.00 sec)

mysql> SELECT * FROM Sales;
+---------+---------+----------+------------+-------------+------------+-------------+
| sale_id | item_id | qty_sold | unit_price | total_price | tax_amount | grand_total |
+---------+---------+----------+------------+-------------+------------+-------------+
|     200 |     100 |       10 |         20 |         200 |      20.00 |         220 |
+---------+---------+----------+------------+-------------+------------+-------------+
1 row in set (0.00 sec)

mysql> insert into Sales(sale_id,item_id,qty_sold) values(201,101,25);
Query OK, 1 row affected (0.01 sec)

mysql> insert into Sales(sale_id,item_id,qty_sold) values(202,102,10);
Query OK, 1 row affected (0.01 sec)

mysql> insert into Sales(sale_id,item_id,qty_sold) values(203,103,20);
Query OK, 1 row affected (0.00 sec)

mysql> SELECT * FROM Item;
+---------+-----------+-------------+------------+------------+
| item_id | item_desc | qty_on_hand | unit_price | category   |
+---------+-----------+-------------+------------+------------+
|     100 | TextBook  |          10 |         20 | book       |
|     101 | milkybar  |           5 |          5 | chocolate  |
|     102 | apple     |          40 |         10 | fruit      |
|     103 | pen       |          80 |          8 | stationary |
+---------+-----------+-------------+------------+------------+
4 rows in set (0.00 sec)

mysql> SELECT * FROM Sales;
+---------+---------+----------+------------+-------------+------------+-------------+
| sale_id | item_id | qty_sold | unit_price | total_price | tax_amount | grand_total |
+---------+---------+----------+------------+-------------+------------+-------------+
|     200 |     100 |       10 |         20 |         200 |      20.00 |         220 |
|     201 |     101 |       25 |          5 |         125 |      37.50 |         163 |
|     202 |     102 |       10 |         10 |         100 |       5.00 |         105 |
|     203 |     103 |       20 |          8 |         160 |      32.00 |         192 |
+---------+---------+----------+------------+-------------+------------+-------------+
4 rows in set (0.00 sec)



Author and Contact:
    Name: Shane.P.Drafahl
    Email: drafahls@gmail.com

About:
    myAccount is a program written in C++ with a MYSQL database that can keep track of 
    expenses and income like a checkbook for checks. It uses Ncurses for a front end
    so this program will be run in a terminal.

Installation:
    To install this program and use it you will need MYSQL on your system or a remote system.
    To setup a local database on your system please follow these instructions for Linux installation. 

    1. sudo apt-get install mysql-server
    2. apt-get install libmysqlcppconn-dev(Debian)(For Non Debian Instalation View http://dev.mysql.com/downloads/connector/cpp/)
    3. sudo apt-get update
    (For Further Help Installing MYSQL Please Visit http://dev.mysql.com/doc/refman/5.7/en/linux-installation.html)
    4. make
    5. ./myAccount

    If you have an existing database to connect to please follow these instructions

    1.make
    2./myAccount

Interfacing With Other Other Programs:

    myAccount uses a MYSQL database so this would allow other programs or users to accessing the data from the user accounts.
    In order for another developer or user to do this I will explain how the data is stored in the MYSQL database. myAccount uses 
    a database called accountDB and it stores all accounts that it will store data with in a table called ACCOUNTS. The table 
    descriptions will be displayed below.Each account has a corresponding table that it stores data with and the name of the table
    it generates will allways be the concatenation of LAST_N,FIRST_N,ID_NUMBER. ID_NUMBER automaticaly increments guaranteeing unique
    table names.
       

ACCOUNTS:
+--------------+-------------+------+-----+---------+----------------+
| Field        | Type        | Null | Key | Default | Extra          |
+--------------+-------------+------+-----+---------+----------------+
| LAST_N       | varchar(60) | NO   |     | NULL    |                |
| FIRST_N      | varchar(60) | NO   |     | NULL    |                |
| ID_NUMBER    | int(255)    | NO   | PRI | NULL    | auto_increment |
| DATE_CREATED | date        | YES  |     | NULL    |                |
+--------------+-------------+------+-----+---------+----------------+

<LAST_N + FIRST_N + ID_NUMBER> Account Table
+------------------+---------------+------+-----+---------+----------------+
| Field            | Type          | Null | Key | Default | Extra          |
+------------------+---------------+------+-----+---------+----------------+
| EXP_INC          | tinyint(1)    | NO   |     | NULL    |                |
| RECURRING        | tinyint(1)    | NO   |     | NULL    |                |
| REC_START        | date          | YES  |     | NULL    |                |
| REC_END          | date          | YES  |     | NULL    |                |
| REC_PERIORD_DAYS | int(255)      | YES  |     | NULL    |                |
| AMOUNT           | double        | NO   |     | NULL    |                |
| DESCRIPTION      | varchar(1000) | NO   |     | NULL    |                |
| ID               | mediumint(9)  | NO   | PRI | NULL    | auto_increment |
+------------------+---------------+------+-----+---------+----------------+

Using myAccount:
    In order to use myAccount the user must first setup a database or use an existing one and compile the source code. After this is
    done in the termnal enter ./myAccount. The User with be greeted with a menu. The first thing the user must do is select "CONNECT TO MYSQL DATABASE"
    and enter the credentials for the MYSQL database(Note if it is a local database for location type "localhost"). Then enter "CONFIRM". If the menu 
    says it is connected you can either disconnect from the database by entering "DISCONNECT" or you can enter "VIEW ACCOUNTS" to view the accounts in
    the database. Once in the accounts menu you can either remove a selected account, add a new account or if you select an account and press enter you
    can see all the income and expenses for that account or you can select "RETURN" to return to the previous menu. The next menu is very similar to the
    previous one.     
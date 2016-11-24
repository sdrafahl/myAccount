 #include "account.h"
 #include "mainMenu.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


using namespace std;
using namespace sql;

MysqlDB::MysqlDB(string loc,string usr,string pass){
    
    try{
    driver = get_driver_instance();
    con = driver->connect(loc,usr,pass);
    con->setSchema("accountDB");
    isConnectedDB=1;
    
    }catch(sql::SQLException &e){
        isConnectedDB=0;
    }
}
int MysqlDB::printAccounts(int sel){
    clear();
    refresh();
    printBorder();
    int counter =0;
    ResultSet *res;
    Statement *stmt;
    init_pair(5,COLOR_GREEN,COLOR_BLACK);
    init_pair(0,COLOR_WHITE,COLOR_BLACK);

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM ACCOUNTS");
    int incr = 0;
    while(res->next()){
        counter++;
        std::ostringstream stringStream;
        stringStream.str("");
        stringStream << "|" << res->getString(1) << "|" << res->getString(2) << "|" << res->getString(3) << "|" << res->getString(4) << "|";
        
        if(sel==incr){
            attron(COLOR_PAIR(5));
        }else{
            attron(COLOR_PAIR(0));
        }
        mvaddstr(incr+1,40,stringStream.str().c_str());
        if(sel==incr){
            attroff(COLOR_PAIR(5));
        }else{
            attroff(COLOR_PAIR(0));
        }
        incr++;

    }
    if(sel==incr){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    string exit = "RETURN";
    mvaddstr(incr+1,40,exit.c_str());
    if(sel==incr){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    delete res;
    delete stmt;
    return counter+1;
}
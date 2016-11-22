 #include "dataBase.h"
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
    isConnected=1;
    
    }catch(sql::SQLException &e){
        isConnected=0;
    }
}
int MysqlDB::printAccounts(int sel){
    clear();
    refresh();
    int counter =0;
    ResultSet *res;
    statement *stmt;
    init_pair(5,COLOR_GREEN,COLOR_BLACK);
    init_pair(0,COLOR_WHITE,COLOR_BLACK);

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM ACCOUNTS");
    int incr = 0;
    while(res->next()){
        counter++;
        std::ostringstream stringStream;
        stringStream.str("");
        stringStream << "|" << res->getInt(1) << "|" << res->getInt(2) << "|" << res->getInt(3) << "|" << res->getInt(4) << "|";
        
        if(sel==incr){
            attron(COLOR_PAIR(5));
        }else{
            attron(COLOR_PAIR(1));
        }
        mvaddstr(incr,40,stringStream.str().c_str());
        if(sel==incr){
            attroff(COLOR_PAIR(5));
        }else{
            attroff(COLOR_PAIR(0));
        }

    }
    return counter;

}
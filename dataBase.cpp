 #include "dataBase.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

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
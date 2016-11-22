#ifndef ACCOUNT
# define ACCOUNT
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <ncurses.h>
#include <sstream>
#include <string>
using namespace std;


class MysqlDB{
    public:
        
        inline ~MysqlDB(){}
        inline void disc(){
            delete con;
        }
        inline int isConnected(){
            return isConnectedDB;
        }
        inline MysqlDB(){}
        MysqlDB(string loc,string usr,string pass);
        int printAccounts(int sel);

    private:
    sql::Driver *driver;
    sql::Connection *con;
    int isConnectedDB;
};
class Account{
    public:
    Account();
    ~Account();
    inline int isConnected(){
        return connectedIndicator;
    }
    inline void connected(){
        connectedIndicator=1;
    }
    inline void disconect(){
        connectedIndicator=0;
        db.disc();
    }
    inline MysqlDB getDB(){
        return db;
    } 
    void addDB(MysqlDB x);
    private:
    int connectedIndicator;
    MysqlDB db;
};



#endif
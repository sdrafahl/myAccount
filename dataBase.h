#ifndef  DATABASE
# define DATABASE

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <ncurses>
#include <sstream>

class MysqlDB{
    public:
        inline ~MysqlDB(){}
        inline void disc(){
            delete stmt;
            delete con;
        }
        int printAccounts(int sel);

    private:
    sql::Driver *driver;
    sql::Connection *con;
    int isConnected;
};

#endif
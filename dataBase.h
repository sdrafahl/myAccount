#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class MysqlDB{
    public:
        inline ~MysqlDB(){}
        inline void disc(){
            delete stmt;
            delete con;
            acc.disconect();
        }
    private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    
        


};
#ifndef ACCOUNT
# define ACCOUNT
#include <sstream>
#include <iostream>

using namespace std;
#include <string>
class Account{
    public:
    inline Account(){

    }
    inline ~Account(){

    }
    inline int isConnected(){
        return connected;
    }
    inline void connected(){
        connected=1;
    }
    inline void disconect(){
        connected=0;
        db.disc();
    }
    inline addDB(MysqlDB x){
        db=x;
    }
    inline MysqlDB getDB(){
        return db;
    } 
    
    private:
    int connected;
    MysqlDB db;
};


extern Account acc;
#endif
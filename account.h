#ifndef ACCOUNT
# define ACCOUNT

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
    }
    inline addDB(MysqlDB x){
        db=x;
    } 
    private:
    string name;
    int connected;
    MysqlDB db;
};


extern Account acc;
#endif
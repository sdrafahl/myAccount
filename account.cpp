#include "account.h"

void Account::addDB(MysqlDB x){
        connectedIndicator=1;
        db=x;
    }
    Account::Account(){

    }
    Account::~Account(){
        
    }
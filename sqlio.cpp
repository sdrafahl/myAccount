#include "init.h"
#include "sqlio.h"
#include <sstream>
#include "account.h"
#include "mainMenu.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

void printMenu(int select);
string location;
string user;
string password;
void startMenu(){
    
    
    int selection=0;
    int intin;
    char in;
    int arrowKeys=0;
    while(1){
        printMenu(selection);
        in = getch();
        intin = (int)in;
        arrowKeys=0;
        if(intin==3){/*Up Arrow*/
            arrowKeys=1;
            selection--;
            if(selection==-1){
                selection=4;
            } 
        }
        if(intin==2){/*Down Arrow*/
            arrowKeys=1;
            selection++;
            if(selection>4){
                selection=0;
            }
        }
        if(!arrowKeys){/*locations, ip address*/
            if(selection==0){    
                if(in=='\a'){
                  location = location.substr(0,location.size()-1);
                }else{
                    location = location + in;
                }
                }
            
            if(selection==1){/*username*/
                if(in=='\a'){
                  user = user.substr(0,user.size()-1);
                }else{
                    user = user + in;
                }
                
            }
            if(selection==2){/*password*/
                
                if(in=='\a'){
                    password = password.substr(0,password.size()-1);
                }else{
                    password = password + in;
                }
                
            }
            if(selection==3){/*confirm*/
                MysqlDB db(location,user,password);
                if(db.isConnected()){
                    clear();
                    init_pair(5,COLOR_GREEN,COLOR_BLACK);
                    attron(COLOR_PAIR(5));
                    string qw = "CONNECTED";
                    mvaddstr(8,38,qw.c_str());
                    attroff(COLOR_PAIR(5));
                    printBorder();
                    refresh();
                    sleep(2);  
                    acc.addDB(db);
                    return;
                }else{
                    clear();
                    init_pair(6,COLOR_RED,COLOR_BLACK);
                    attron(COLOR_PAIR(6));
                    string qw = "FAILED TO CONNECT";
                    mvaddstr(8,38,qw.c_str());
                    attroff(COLOR_PAIR(6));
                    printBorder();
                    refresh();
                    sleep(2);  
                    return;
                }
            }
            if(selection==4){/*back*/
                if(in=='\n'){
                    return;
                }
            }
        }
    }
    

    }



void printMenu(int select){
    
    init_pair(5,COLOR_GREEN,COLOR_BLACK);
    init_pair(0,COLOR_WHITE,COLOR_BLACK);
    clear();
    refresh();
    printBorder();
    if(select==0){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
        
    std::ostringstream stream;
    string field = "ENTER IP OR localhost: ";
    stream.str("");
    stream << field << location;
    mvaddstr(1,40,stream.str().c_str());
    if(select==0){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }
    
    if(select==1){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    
    std::ostringstream stream1;
    string field1 = "MYSQL USERNAME: ";
    stream1.str("");
    stream1 << field1 << user;
    
    mvaddstr(2,40,stream1.str().c_str());
    if(select==1){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }
    
    if(select==2){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    
    std::ostringstream stream2;
    string field2 = "MYSQL PASSWORD: ";
    stream2.str("");
    int total = password.size();
    int incra=0;
    stream2 << field2;
    for(incra=0;incra<total;incra++){
        stream2 << "*";
    }
    mvaddstr(3,40,stream2.str().c_str());
    if(select==2){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    if(select==3){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    string menu = "CONFIRM";
    mvaddstr(4,40,menu.c_str());
    if(select==3){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    if(select==4){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    menu = "BACK";
    mvaddstr(5,40,menu.c_str());
    if(select==4){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }



}

void controlAccounts(){
    int selection =0;
    int val = 0;
    int total = 0;
    while(1){
        
        MysqlDB te = acc.getDB();
        total = te.printAccounts(selection);
        

        val = getch();
        
        if(val==258){/*Down Arrow*/
            selection++;
            if(selection==total){
                selection=0;
            }
        }
        if(val==259){/*Up Arrow*/
            selection--;
            if(selection==-1){
                selection=total-1;
            }
        }
        if(val==10){
            if(total-1==selection){
                return;
            }
        }
    }    
}


void control_a_Account(){
    int selection = 0;
    
}
void print_a_Account(int select){
     init_pair(5,COLOR_GREEN,COLOR_BLACK);
     init_pair(0,COLOR_WHITE,COLOR_BLACK);
     clear();
     refresh();
     printBorder();
     /*Prints Border Between Data and Computed Data*/
     int val = 0;
     string border = "#";
     for(val=0;val<80;val++){
         mvaddstr(20,val,border.c_str());
     }
     /*Prints Data About the Account*/
     ResultSet& res;
     Statement& stmt;

     std::ostringstream ss;
     string command = "SELECT * FROM ACCOUNTS LIMIT ";
     ss.str("");
     ss << command << select << ",1";
     stmt = acc.getStatement();
     res = stmt.executeQuery(ss.str());

}



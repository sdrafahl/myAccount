#include "sqlio.h"
void startMenu(){
    string location;
    string user;
    string password;
    
    int selection=0;
    int intin;
    char in;
    int arrowKeys=0;
    while(1){
        printMenu(selection);
        in = getch();
        intin = (int)in;
        arrowKeys=0;
        if(intin==259){/*Up Arrow*/
            arrowKeys=1;
            selection--;
            if(selection==-1){
                selection=4;
            } 
        }
        if(initin==258){/*Down Arrow*/
            arrowKeys=1;
            selection++;
            if(selection>4){
                selection==0;
            }
        }
        if(!arrowKeys){
            if(selection==0){/*locations, ip address*/
                std::ostringstream input;
                input.str(location);
                 input << in;
                 location = input.str();
            }
            if(selection==1){/*username*/
                std::ostringstream input;
                input.str(user);
                input << in;
                user = input.str();
            }
            if(selection==2){/*password*/
                std::ostringstream input;
                input.str(password);
                input << in;
                password = input.str();
            }
            if(selection==3){/*confirm*/
                MysqlDB db(location,user,password);
                if(db.isConnected){
                    string qw = "CONNECTED";
                    mvaddstr(0,40,qw.c_str());
                    sleep(2000);  
                    acc.addDB(db);
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


printMenu(int select){
    init_pair(5,COLOR_GREEN,COLOR_BLACK);
    init_pair(0,COLOR_WHITE,COLOR_BLACK);
    clear();
    refresh();
    if(select==0){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
        
    std::ostringstream stream;
    stream.str("ENTER IP OR localhost: ");
    stream << location;
    mvaddstr(0,40,stream.str().c_str());
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
    stream1.str("MYSQL USERNAME: ");
    stream1 << user;
    
    mvaddstr(1,40,stream1.str().c_str());
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
    stream2.str("MYSQL PASSWORD: ");
    stream2 << user;
    mvaddstr(2,40,stream2.str().c_str());
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
    mvaddstr(3,40,menu.c_str());
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
    mvaddstr(4,40,menu.c_str());
    if(select==4){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }



}
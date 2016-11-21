#include <ncurses.h>
#include <string>
#include "mainMenu.h"
#include "account.h"

void startMainMenu(){
    int selection =0;
    int ch;
    while(1){
    printMainMenu(selection);
        while(1){
            ch = getch();
            if(ch){
                break;
            }
        }
    switch(ch){

        case 258:/*DOWN ARROW*/
            selection--;
            if(selection==-1){
                selection=3;
            }
        break;
        case 259:/*UP ARROW*/
            selection++;
            if(selection==4){
                selection=0;
            }
        break;
        case '\n':/*ENTER*/
            switch(selection){
                case 0:/*View Account*/
                    if(acc.isConnected()){

                    }
                break;
                case 1:/*Make a new account*/
                    if(acc.isConnected()){

                    }
                break;
                case 2:/*Connect to MySQL*/
                    startMenu();
                break;
                case 3:/*Exit and Save*/
                    if(acc.isConnected()){
                        /*Save Data if Connected*/
                    }
                    exit(0);
                break;
            }
        break;

    }
    
    }
    



}

void printMainMenu(int select){
    
    init_pair(5,COLOR_GREEN,COLOR_BLACK);
    init_pair(0,COLOR_WHITE,COLOR_BLACK);
    clear();
    refresh();
    if(select==0){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    string menu = "VIEW ACCOUNTS";
    mvaddstr(0,40,menu.c_str());
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
    menu = "MAKE A NEW ACCOUNT";
    mvaddstr(1,40,menu.c_str());
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
    menu = "CONNECT TO LOCAL MYSQL DATABASE";
    mvaddstr(2,40,menu.c_str());
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
    menu = "EXIT";
    mvaddstr(2,40,menu.c_str());
    if(select==3){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

}

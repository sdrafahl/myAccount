#include <ncurses.h>
#include "init.h"
#include <string>
#include "mainMenu.h"
#include "account.h"
#include "sqlio.h"


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
            selection++;
            if(selection==4){
                selection=0;
            }
        break;
        case 259:/*UP ARROW*/
            selection--;
            if(selection==-1){
                selection=3;
            }
        break;
        case 10:/*ENTER*/
            switch(selection){
                case 0:/*View Account*/
                    if(acc.isConnected()){
                        controlAccounts();
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
                    endwin();
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
    
    printBorder();
    
    if(select==0){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    string menu = "VIEW ACCOUNTS";
    mvaddstr(2,33,menu.c_str());
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
    mvaddstr(4,31,menu.c_str());
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
    menu = "CONNECT TO MYSQL DATABASE";
    mvaddstr(6,28,menu.c_str());
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
    mvaddstr(8,38,menu.c_str());
    if(select==3){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

}

void printBorder(){
    int x=0;
    int y=0;
    string d = "#";
    for(y=0;y<80;y++){/*Top*/
        mvaddstr(0,y,d.c_str());
    }
    for(y=0;y<80;y++){/*Bottom*/
        mvaddstr(25,y,d.c_str());
    }
    for(x=0;x<26;x++){/*Left Side*/
        mvaddstr(x,0,d.c_str());
    }
    for(x=0;x<26;x++){/*Right Side*/
        mvaddstr(x,80,d.c_str());
    }
} 

void printBorderWithScale(float scalex, float scaley){
    float x=0;
    float y=0;
    string d = "#";
    for(y=0;y<80*scalex;y++){/*Top*/
        mvaddstr(0,y,d.c_str());
    }
    for(y=0;y<80*scalex;y++){/*Bottom*/
        mvaddstr(25*scaley,y,d.c_str());
    }
    for(x=0;x<26*scaley;x++){/*Left Side*/
        mvaddstr(x,0,d.c_str());
    }
    for(x=0;x<26*scaley;x++){/*Right Side*/
        mvaddstr(x,80*scalex,d.c_str());
    }
} 
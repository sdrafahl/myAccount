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
                case 1:/*Connect to MySQL*/
                    startMenu();
                break;
                case 2:/*Disconect*/
                    acc.disconect();
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
    init_pair(6,COLOR_RED,COLOR_BLACK);
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
    menu = "CONNECT TO MYSQL DATABASE";
    mvaddstr(4,28,menu.c_str());
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
    menu = "DISCONNECT";
    mvaddstr(6,35,menu.c_str());
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

    /*Status Information*/
     int val = 0;
     string border = "#";
     for(val=0;val<80;val++){
         mvaddstr(20,val,border.c_str());
     }

     if(acc.isConnected()){
         attron(COLOR_PAIR(5));
         string disp = "CONNECTED";
         mvaddstr(21,2,disp.c_str());
         disp = "SERVER: ";
         disp+= acc.location;
         mvaddstr(22,2,disp.c_str());
         disp = "USER: ";
         disp+=acc.user;
         mvaddstr(23,2,disp.c_str());
         attroff(COLOR_PAIR(5));

     }else{
         attron(COLOR_PAIR(6));
         string disp = "NOT CONNECTED";
         mvaddstr(21,2,disp.c_str());
         attroff(COLOR_PAIR(6));
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
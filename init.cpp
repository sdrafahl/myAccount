#include "init.h"
#include "account.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "account.h"

Account acc;
void setup(){
    initscr(); /*starts curses mode*/
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
}

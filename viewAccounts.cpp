#include "viewAccounts.h"

void controlAccounts(){
    int selection =0;
    int val = 0;
    int total = 0;
    while(1){
        total = acc.getDB().printAccounts(selection);
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
    }
    
    
    
}
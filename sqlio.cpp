#include "init.h"
#include "sqlio.h"
#include <sstream>
#include "account.h"
#include "mainMenu.h"
#include <ctime>
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
struct AccountData;
AccountData print_a_Account(int select,int internal);
void control_a_Account(int selection);
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
            }else{
                control_a_Account(selection);
            }
        }
    }    
}

struct AccountData {
    int count;
    float total;
};
/*Requires Digit Format*/
static int getDaysOfMonth(int month){
    switch(month){
        case 1: /*January*/
            return 31;
        break;
        case 2:/*February*/
            return 28;
        break;
        case 3:/*March*/
            return 31;
        break;
        case  4:/*April*/
            return 30;
        break;
        case 5: /*May*/
            return 31;
        break;
        case 6:/*june*/
            return 30;
        break;
        case 7:/*July*/
            return 31;
        break;
        case 8:/*August*/
            return 31;
        break;
        case 9:/*September*/
            return 30;
        break;
        case 10:/*October*/
            return 31;
        break;
        case 11: /*November*/
            return 30;
        break;
        case 12:/*December*/
            return 31;
        break;
    
    }
    /*Incase Somthing Goes Wrong it returns the Average*/
    return 30;
}
static string getCurrentDateTime() {
    stringstream currentDateTime;
    
    time_t ttNow = time(0);
    tm *ltm = localtime(&ttNow);

    currentDateTime << 1900 + ltm->tm_year;
    if(1 + ltm->tm_mon<=9){
        currentDateTime << "0" << 1 + ltm->tm_mon;
    }else{
        currentDateTime << 1 + ltm->tm_mon;
    }
    if(ltm->tm_mday<=9){
        currentDateTime << "0" << ltm->tm_mday;
    }else{
        currentDateTime << ltm->tm_mday;
    }
    free(ltm);
    return currentDateTime.str();
}
/*Returns Absolute Value of Total Recurring Payment*/
static float getRecurringPayments(string dateFrom, string dateTo, string period, string amount){
    /*Does Not Account for Leap Years*/
    float totalDays = 0;
    /*Calculating the Number of Days Between The Dates Given with MYSQL Format*/
    float year2Val = 0;
    float month2Val = 0;
    float day2Val = 0;

    
    float year1Val = 0;
    float month1Val =0;
    float day1Val = 0;

    /*Second Date Given*/
    stringstream year2;
    char in;
    float counter=0;
    year2.str("");
    in = dateTo.at(counter);
    while(in!='-'){
        year2 << in;
        counter++;
        in = dateTo.at(counter);
    }
    year2 >> year2Val;

    stringstream month2;
    in = ' ';
    counter++;
    month2.str("");
    in = dateTo.at(counter);
    while(in!='-'){
        month2 << in;
        counter++;
        in = dateTo.at(counter);
    }
    month2 >> month2Val;

    stringstream day2;
    in = ' ';
    counter++;
    day2.str("");
    in = dateTo.at(counter);
    while(in!='-'){
        day2 << in;
        counter++;
        in = dateTo.at(counter);
    }
    day2 >> day2Val;

    /*First Date Given*/

    stringstream year1;
    in = ' ' ;
    counter=0;
    year1.str("");
    in = dateTo.at(counter);
    while(in!='-'){
        year1 << in;
        counter++;
        in = dateTo.at(counter);
    }
    year1 >> year1Val;

    stringstream month1;
    in = ' ';
    counter++;
    month1.str("");
    in = dateTo.at(counter);
    while(in!='-'){
        month1 << in;
        counter++;
        in = dateTo.at(counter);
    }
    month1 >> month1Val;

    stringstream day1;
    in = ' ';
    counter++;
    day1.str("");
    in = dateTo.at(counter);
    while(in!='-'){
        day1 << in;
        counter++;
        in = dateTo.at(counter);
    }
    day1 >> day1Val;

    float yearDif = year2Val - year1Val;
    yearDif*=365;
    
    float monthCount;
    float monthDif = 0;
    for(monthCount=month1Val;monthCount<month2Val;monthCount++){
        monthDif += getDaysOfMonth(monthCount);
    }
    float dayDif = day2Val - day1Val;
    totalDays= dayDif + monthDif + yearDif;

    stringstream convert(period);
    float periodVal = 0;
    convert >> periodVal;
    
    string current = getCurrentDateTime();
    string year = current.substr(0,4);/*This Program Will crash beyond the year 9999*/
    string month = current.substr(4,2);
    string day = current.substr(6,2);

    /*Convert Months To Days*/
    stringstream con;
    con.str(month);
    float currentMonthVal =0;
    con >> currentMonthVal;
    
    monthCount = 0;
    monthDif = 0;
    for(monthCount=month1Val;monthCount<currentMonthVal;monthCount++){
        monthDif += getDaysOfMonth(monthCount);
    }
    stringstream var1;
    var1.str(year);
    float currentYearVal = 0;
    var1 >> currentYearVal;
    
    stringstream dayConverter;
    dayConverter.str(day);
    float currentDayVal = 0;
    dayConverter >> currentDayVal;

    float currentDayDif = currentDayVal - day1Val;
    float currentInitDif = ((currentYearVal - year1Val)*365) + monthDif + currentDayDif;

    stringstream periodConverter;
    periodConverter.str(period);
    float perVal = 0;
    periodConverter >> perVal;

    stringstream ammountConverter;
    ammountConverter.str(amount);
    float amountVal = 0;
    ammountConverter >> amountVal;

    float grandTotal = 0;
    float incramentor;
    for(incramentor = 0;incramentor<=totalDays && incramentor<currentInitDif;incramentor+=perVal){
        grandTotal+=amountVal;
    } 
    return grandTotal;

}

void control_a_Account(int selection){
    int internal =0;
    int val = 0;
    AccountData data;
    while(1){
        
        data = print_a_Account(selection,internal);
        

        val = getch();
        
        if(val==258){/*Down Arrow*/
            internal++;
            if(internal==data.total){
                internal=0;
            }
        }
        if(val==259){/*Up Arrow*/
            internal--;
            if(internal==-1){
                internal=data.total-1;
            }
        }
        if(val==10){
            if(data.total==internal){
                return;
            }
        }
    }    
    
}

AccountData print_a_Account(int select,int internal){
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
     ResultSet* res;
     Statement* stmt;

     std::ostringstream ss;
     string command = "SELECT * FROM ACCOUNTS LIMIT ";
     ss.str("");
     ss << command << select << ",1";
     stmt = acc.getStatement();
     res = stmt->executeQuery(ss.str());
     AccountData rets;
     while(res->next()){
         std::ostringstream con;
         con.str("");
         con << res->getString(1) << res->getString(2) << res->getString(3);
         /*con should hold the table name*/
         delete stmt;
         delete res;
         stmt = acc.getStatement();
         string command = "SELECT * FROM ";
         res = stmt->executeQuery(command + con.str());
         int counter=0;
         float total=0;/*Total Amount*/
         while(res->next()){
             counter++;
             string row = "";
             row = row + res->getString(1) + "|" + res->getString(2) + "|" + res->getString(3) + "|" + res->getString(4) + "|" + res->getString(5) + "|" + res->getString(6) + "|" + res->getString(7) + "|" + res->getString(8) + "|";
             if((counter-1)==internal){
                 attron(COLOR_PAIR(5));
             }else{
                 attron(COLOR_PAIR(0));
             }
             mvaddstr(counter,35,row.c_str());
             if((counter-1)==internal){
                 attroff(COLOR_PAIR(5));
             }else{
                 attroff(COLOR_PAIR(0));
             }

             if(res->getString(2)=="1"){
                 /*Recurring*/
                 float amount = getRecurringPayments(res->getString(3),res->getString(4),res->getString(5),res->getString(6));
                 /*If it is an expense*/
                if(res->getString(1)=="1"){
                    amount*=-1;
                }
                 total+=amount;
                }else{
                 /*Not Recurring*/
                 stringstream conver;
                 conver.str(res->getString(6));
                 float num;
                 conver >> num;
                 if(res->getString(1)=="1"){
                    num*=-1;
                }
                total+=num;
             }
         }
         if((counter-1)==internal){
                 attron(COLOR_PAIR(5));
             }else{
                 attron(COLOR_PAIR(0));
             }
             string ret = "RETURN";
             mvaddstr(counter+1,35,ret.c_str());
             if((counter-1)==internal){
                 attroff(COLOR_PAIR(5));
             }else{
                 attroff(COLOR_PAIR(0));
             }
         
         
         rets.total = total;
         rets.count = counter;
     }
        return rets;
}



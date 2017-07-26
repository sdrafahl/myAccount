#include "init.h"
#include "sqlio.h"
#include <sstream>
#include "account.h"
#include "mainMenu.h"
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
struct AccountData;
struct AccountD;
struct NewAccountData;
AccountData print_a_Account(float scale_x,float scale_y,int select,int internal);
void control_a_Account(int selection);
void printMenu(int select);
void removeColumn(AccountData d,int sel);
void addToDatabase(AccountData d,AccountD da);
void printDataEntry(AccountD d,int sel);
void newDataEntry(AccountData da);
void addAccount();
void addTables(NewAccountData d);
void printAccount(NewAccountData d,int selection);

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
                    usleep(2);  
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
                    usleep(2);  
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
                if(selection==-1){
                    selection=0;
                }
            }
        }
        if(val==114){/*Remove*/
            if(selection!=total){/*If Not Return*/
                ResultSet* res;
                Statement* stmt;
                std::ostringstream ss;
                string command = "SELECT * FROM ACCOUNTS LIMIT ";
                ss.str("");
                ss << command << selection << ",1";
                stmt = acc.getStatement();
     
                res = stmt->executeQuery(ss.str());
                res->next();
                std::ostringstream con;
                string id = res->getString(3);
                string tableToDelete = res->getString(1) + res->getString(2) + res->getString(3);
                command = "DELETE FROM ACCOUNTS WHERE ID_NUMBER=" + id;

                delete stmt;
                delete res;
                stmt = acc.getStatement();
                stmt->execute(command);
                delete stmt;
                stmt = acc.getStatement();
                command = "DROP TABLE IF EXISTS " + tableToDelete;
                stmt->execute(command);
                delete stmt;
            }
        }
        if(val==97){/*Add A New Account*/
            if(selection!=total){
                addAccount();
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

    float scalex;
    float scaley;

    string table;
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
    int onetwo =0;
    for(onetwo=0;onetwo<1;onetwo++){
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
    in = dateFrom.at(counter);
    while(in!='-'){
        year1 << in;
        counter++;
        in = dateFrom.at(counter);
    }
    year1 >> year1Val;

    stringstream month1;
    in = ' ';
    counter++;
    month1.str("");
    in = dateFrom.at(counter);
    while(in!='-'){
        month1 << in;
        counter++;
        in = dateFrom.at(counter);
    }
    month1 >> month1Val;

    stringstream day1;
    in = ' ';
    counter++;
    day1.str("");
    in = dateFrom.at(counter);
    
        day1 << in;
        counter++;
        in = dateFrom.at(counter);
    
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
        
        if(data.count){
            data = print_a_Account(data.scalex,data.scaley,selection,internal);
        }else{
          data = print_a_Account(1,1,selection,internal);  
        }
        
        

        val = getch();
        if(val==97){
            newDataEntry(data);
        }
        if(val==258){/*Down Arrow*/
            internal++;
            if(internal==data.count+1){
                internal=0;
            }
        }
        if(val==259){/*Up Arrow*/
            internal--;
            if(internal==-1){
                internal=data.count-1;
                if(internal==-1){
                    internal=0;
                }
            }
        }
        if(val==114){
            if(!data.count==internal){
                removeColumn(data,internal);
            }
        }
        if(val==10){
            if(data.count==internal){
                return;
            }

        }
    }    
    
}

struct NewAccountData{
    string last;
    string first;
    string date;
};
void addAccount(){
    int selection=0;
    NewAccountData d;
    while(1){
        printAccount(d,selection);
        char in = getch();
         if(in=='\002'){/*Down Arrow*/
            selection++;
            if(selection==5){
                selection=0;
            }
        }
        if(in=='\003'){/*Up Arrow*/
            selection--;
            if(selection==-1){
                selection=0;
            }   
        }
        if(in=='\n'){/*Enter Key*/
                if(selection==3){/*Return*/
                return;
            }
            if(selection==4){/*Make a New Account*/
                addTables(d);
                return;
            }
        }
        if(in=='\a'){/*Backspace Key*/
            if(selection==0){
                d.last = d.last.substr(0,d.last.size()-1);
            }
            if(selection==1){
                d.first = d.first.substr(0,d.first.size()-1);
            }
            if(selection==2){
                d.date = d.date.substr(0,d.date.size()-1);
            }
        }
        if(in !='\a' && in !='\n' && in!='\002' && in!='\003'){
            if(selection==0){
                d.last+=in;
            }else{
                if(selection==1){
                    d.first+=in;
                }else{
                    if(selection==2){
                        d.date+=in;
                    }
                }
            }
        }     
    }
    
}

void addTables(NewAccountData d){
    string command = "INSERT INTO ACCOUNTS VALUES('" + d.last + "','" + d.first + "',NULL,'" + d.date + "')";
     Statement* stmt;
     stmt = acc.getStatement();
     stmt->execute(command);

     delete stmt;


     ResultSet* res;
     command = "SELECT * FROM ACCOUNTS WHERE LAST_N ='" + d.last + "' AND FIRST_N =" + "'" + d.first + "'";
     stmt = acc.getStatement();
     res = stmt->executeQuery(command.c_str());
     delete stmt;
     while(res->next()){
         stmt = acc.getStatement();
         command = "CREATE TABLE IF NOT EXISTS " + d.last + d.first + res->getString(3) +
          "(EXP_INC BOOL NOT NULL,RECURRING BOOL NOT NULL,REC_START DATE NULL,REC_END DATE NULL,REC_PERIORD_DAYS INT(255) NULL,AMOUNT DOUBLE NOT NULL,DESCRIPTION VARCHAR(1000) NOT NULL,ID MEDIUMINT(9) NOT NULL AUTO_INCREMENT,PRIMARY KEY (ID));" ;
         stmt->execute(command);
         delete stmt;
     }
     delete res;
     

}
void printAccount(NewAccountData d,int selection){
     init_pair(5,COLOR_GREEN,COLOR_BLACK);
     init_pair(0,COLOR_WHITE,COLOR_BLACK);
     clear();
     refresh();
     printBorder();

     string disp = "Last Name: " + d.last;

     if(selection==0){
         attron(COLOR_PAIR(5));
     }else{
         attron(COLOR_PAIR(0));
     }
     mvaddstr(1,2,disp.c_str());
     if(selection==0){
         attroff(COLOR_PAIR(5));
     }else{
         attroff(COLOR_PAIR(0));
     }

     disp = "First Name: " + d.first;

     if(selection==1){
         attron(COLOR_PAIR(5));
     }else{
         attron(COLOR_PAIR(0));
     }
     mvaddstr(3,2,disp.c_str());
     if(selection==1){
         attroff(COLOR_PAIR(5));
     }else{
         attroff(COLOR_PAIR(0));
     }
        
     disp = "Date Created(yyyy-mm-dd): " + d.date;

     if(selection==2){
         attron(COLOR_PAIR(5));
     }else{
         attron(COLOR_PAIR(0));
     }
     mvaddstr(5,2,disp.c_str());
     if(selection==2){
         attroff(COLOR_PAIR(5));
     }else{
         attroff(COLOR_PAIR(0));
     }

     disp = "RETURN"; 

     if(selection==3){
         attron(COLOR_PAIR(5));
     }else{
         attron(COLOR_PAIR(0));
     }
     mvaddstr(7,2,disp.c_str());
     if(selection==3){
         attroff(COLOR_PAIR(5));
     }else{
         attroff(COLOR_PAIR(0));
     }

     disp = "CONFIRM"; 

     if(selection==4){
         attron(COLOR_PAIR(5));
     }else{
         attron(COLOR_PAIR(0));
     }
     mvaddstr(9,2,disp.c_str());
     if(selection==4){
         attroff(COLOR_PAIR(5));
     }else{
         attroff(COLOR_PAIR(0));
     }


}



AccountData print_a_Account(float scale_x,float scale_y,int select,int internal){
     init_pair(5,COLOR_GREEN,COLOR_BLACK);
     init_pair(0,COLOR_WHITE,COLOR_BLACK);
     float scalex = scale_x;
     float scaley = scale_y;
     int width = 80*scalex;
     int height = 20*scaley;

     clear();
     refresh();
     printBorder();
     //printBorderWithScale(scalex,scaley);
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
         rets.table=con.str();
         int counter=0;
         float total=0;/*Total Amount*/
         while(res->next()){
             counter++;
             string row = "";
             
             
             if(res->getString(1)=="1"){
                 row += "Expense";
             }else{
                 row += "Income";
             }
             row += "|";
             if(res->getString(2)=="1"){
                 row += "Recurring";
             }else{
                 row += "Non-Recurring";
             }
             row += "|";
             if(res->getString(2)=="1"){
                 row += res->getString(3);
                 row += "|";
                 row += res->getString(4);
                 row += "|";
                 row += "Period of Days: " + res->getString(5);
                 row += "|";

             }else{
                 row += "N/A";
                 row += "|";
                 row += "N/A";
                 row += "|";
                 row += "N/A";
                 row += "|";
             }
             
             row = row + "$" + res->getString(6) + "|" + "DESC:" + res->getString(7) + "|" + "ID:" + res->getString(8) + "|";
             
             int length = row.size();

             if(width-length < 10 || length > width){
                 scalex+=.25;
                 width = .25 * width;
             }

             
             
             if((counter-1)==internal){
                 attron(COLOR_PAIR(5));
             }else{
                 attron(COLOR_PAIR(0));
             }
             mvaddstr(counter,1,row.c_str());
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
         if((counter)==internal){
                 attron(COLOR_PAIR(5));
             }else{
                 attron(COLOR_PAIR(0));
             }
             string ret = "RETURN";
             mvaddstr(counter+1,1,ret.c_str());
             if((counter)==internal){
                 attroff(COLOR_PAIR(5));
             }else{
                 attroff(COLOR_PAIR(0));
             }
         
         
         rets.total = total;
         rets.count = counter;
         
         init_pair(7,COLOR_RED,COLOR_BLACK);
        if(total>=0){
            attron(COLOR_PAIR(5));
        }else{
            attron(COLOR_PAIR(7));
        }
         stringstream display;
         string totaldisp = "TOTAL: $";
         display.str("");
         
        // float rounded = floorf(total*100)/100;
        // rounded+=.01;
         display << total;
         
         totaldisp += display.str();
         mvaddstr(21,1,totaldisp.c_str());
         if(total>=0){
            attroff(COLOR_PAIR(5));
        }else{
            attroff(COLOR_PAIR(7));
        }

     }
        if(height-rets.count<5 || rets.count>=height){
            scaley*=.25;
        }
        
        string rem = "REMOVE - r";
        mvaddstr(22,20,rem.c_str());
        
        rem = "NEW - a";
        mvaddstr(21,20,rem.c_str());

        rets.scalex = scalex;
        rets.scaley = scaley;
        return rets;
}

/*
INSERT INTO RobWood5 VALUES (  0 ,1 ,'2016-01-01','2016-05-15' ,1,20 ,'JOB' ,NULL);
*/

void removeColumn(AccountData d,int sel){
    
    ResultSet* res;
     Statement* stmt;

     std::ostringstream ss;
     ss.str("");
     ss << sel;
     string command = "SELECT * FROM " + d.table + " LIMIT " + ss.str() + ",1";
     
     
     stmt = acc.getStatement();
     res = stmt->executeQuery(command);
     res->next();
     std::ostringstream con;
     con.str("");
     con << res->getString(8);
     /*con should hold the table name*/
     delete stmt;
     delete res;
     stmt = acc.getStatement();
     command = "DELETE FROM " + d.table + " WHERE ID= '" + con.str() +"'";
     stmt->execute(command);

     
}
struct AccountD{
    string EXP_INC;
    string RECURRING;
    string REC_START;
    string REC_END;
    string PERIOD;
    string amount;
    string description;
};
void newDataEntry(AccountData da){
    int select = 0;
    AccountD d;
    
    while(1){
        printDataEntry(d,select);
        int val = getch();
        char charval = (char)val;
        if(val==258){/*Down Arrow*/
            select++;
            if(select==9){
                select=0;
            }
        }
        if(val==259){/*Up Arrow*/
            select--;
            if(select==-1){
                select=8;
               }
        }
        if(val!=10 && val!=259 && val!=258 && select!=7 && select !=8){
            if(charval=='\a'){
                    if(select==0){
                        d.EXP_INC = d.EXP_INC.substr(0,d.EXP_INC.size()-1);
                    }
                    if(select==1){
                        d.RECURRING = d.RECURRING.substr(0,d.RECURRING.size()-1);
                    }
                    if(select==2){
                        d.REC_START = d.REC_START.substr(0,d.REC_START.size()-1);
                    }
                    if(select==3){
                        d.REC_END = d.REC_END.substr(0,d.REC_END.size()-1);
                    }
                    if(select==4){
                        d.PERIOD = d.PERIOD.substr(0,d.PERIOD.size()-1);
                    }
                    if(select==5){
                        d.amount = d.amount.substr(0,d.amount.size()-1);
                    }
                    if(select==6){
                        d.description = d.description.substr(0,d.description.size()-1);
                    }
            }else{
                 
                    if(select==0){
                        d.EXP_INC+=charval;
                    }
                    if(select==1){
                        d.RECURRING+=charval;
                    }
                    if(select==2){
                        d.REC_START+=charval;
                    }
                    if(select==3){
                        d.REC_END+=charval;
                    }
                    if(select==4){
                        d.PERIOD+=charval;
                    }
                    if(select==5){
                        d.amount+=charval;
                    }
                    if(select==6){
                        d.description+=charval;
                    }
            }
        }
        if(val==10){
            if(select==7){/*Return*/
                return;
            }
            if(select==8){/*Confirm*/
                addToDatabase(da,d);
                return;
            }
        }

    }

}

void addToDatabase(AccountData d,AccountD da){
    string command;
    string pos_neg;
    if(da.EXP_INC=="I" || da.EXP_INC=="i"){
        pos_neg="0";
    }else{
        pos_neg="1";
    }
    string rec;
    if(da.RECURRING=="y" || da.RECURRING=="Y"){
        rec="1";
    }else{
        rec="0";
    }
    if(da.RECURRING=="y"){
        command = "INSERT INTO " + d.table + " VALUES (" + pos_neg + "," + rec +","+ "'" +da.REC_START + "'" +","+ "'" +da.REC_END+ "'" +","+da.PERIOD+","+da.amount+", '"+da.description +"',"+"NULL);";
    }else{
        command = "INSERT INTO " + d.table + " VALUES (" + pos_neg + "," + rec +","+ "NULL" +","+"NULL" +",NULL,"+da.amount+", '"+da.description +"',"+"NULL);";
    }
    Statement* stmt;
    stmt = acc.getStatement();
    try{
    stmt->execute(command);
    }catch(sql::SQLException &e){
        string message = "ERROR ADDING DATA";
        init_pair(6,COLOR_RED,COLOR_BLACK);
        attron(COLOR_PAIR(6));
        mvaddstr(10,35,message.c_str());
        usleep(1);
        attroff(COLOR_PAIR(6));
    }
}

void printDataEntry(AccountD d,int sel){
    init_pair(5,COLOR_GREEN,COLOR_BLACK);
    init_pair(0,COLOR_WHITE,COLOR_BLACK);
    clear();
    refresh();
    printBorder();
    if(sel==0){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    std::ostringstream stream;
    string field = "Expense or Income,Enter i or e: ";
    stream.str("");
    stream << field << d.EXP_INC;
    mvaddstr(1,1,stream.str().c_str());
    if(sel==0){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    if(sel==1){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    field = "Recuring,Enter y or n:  ";
    stream.str("");
    stream << field << d.RECURRING;
    mvaddstr(2,1,stream.str().c_str());
    if(sel==1){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    string info = "If Recuring Enter In Dates in Format yyyy-mm-dd";
    mvaddstr(3,1,info.c_str());

    if(sel==2){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    field = "Enter Recurring Start Date:  ";
    stream.str("");
    stream << field << d.REC_START;
    mvaddstr(4,1,stream.str().c_str());
    if(sel==2){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    if(sel==3){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    field = "Enter Recurring End Date:  ";
    stream.str("");
    stream << field << d.REC_END;
    mvaddstr(5,1,stream.str().c_str());
    if(sel==3){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    if(sel==4){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    field = "Recurring Period in Days:   ";
    stream.str("");
    stream << field << d.PERIOD;
    mvaddstr(6,1,stream.str().c_str());
    if(sel==4){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    if(sel==5){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    field = "Amount: ";
    stream.str("");
    stream << field << d.amount;
    mvaddstr(7,1,stream.str().c_str());
    if(sel==5){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    if(sel==6){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    field = "Description: ";
    stream.str("");
    stream << field << d.description;
    mvaddstr(8,1,stream.str().c_str());
    if(sel==6){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }


    if(sel==7){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    field = "Return";
    mvaddstr(9,1,field.c_str());
    if(sel==7){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }

    if(sel==8){
        attron(COLOR_PAIR(5));
    }else{
        attron(COLOR_PAIR(0));
    }
    field = "Confirm";
    mvaddstr(10,1,field.c_str());
    if(sel==8){
        attroff(COLOR_PAIR(5));
    }else{
        attroff(COLOR_PAIR(0));
    }


}
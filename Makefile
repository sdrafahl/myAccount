All:
	g++ -Wall -g -O -c viewAccounts.cpp -lncurses
	g++ -Wall -g -O -c sqlio.cpp -lncurses
	g++ -Wall -g -O -c mainMenu.cpp -lncurses
	g++ -Wall -g -O -c init.cpp -lncurses
	g++ -Wall -g -O -c dataBase.cpp -lncurses
	g++ -Wall -g -O -c account.cpp -lncurses
	ar -cvq program.a viewAccounts.o sqlio.o mainMenu.o init.o dataBase.o account.o
	g++ -Wall -ggdb main.cpp -o myAccount program.a -lncurses -lmysqlcppconn
Clean:
	bash clean.bash

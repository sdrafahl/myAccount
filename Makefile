All:
	g++ -Wall -g -O -c -O0 sqlio.cpp -lncurses
	g++ -Wall -g -O -c -O0 mainMenu.cpp -lncurses
	g++ -Wall -g -O -c -O0 init.cpp -lncurses
	g++ -Wall -g -O -c -O0  dataBase.cpp -lncurses
	g++ -Wall -g -O -c -O0 account.cpp -lncurses
	ar -cvq program.a sqlio.o mainMenu.o init.o dataBase.o account.o
	g++ -Wall -ggdb -O0 main.cpp -o myAccount program.a -lncurses -lmysqlcppconn
Clean:
	bash clean.bash

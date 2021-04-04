all: Mastermind.exe

Mastermind.exe: OBJETOS/mainMaster.o OBJETOS/config.o OBJETOS/partida.o OBJETOS/menus.o OBJETOS/varias.o OBJETOS/jugadas.o OBJETOS/tiempos.o OBJETOS/informes.o OBJETOS/ranking.o OBJETOS/franjas.o
	gcc -o Mastermind.exe OBJETOS/mainMaster.o OBJETOS/tiempos.o OBJETOS/config.o OBJETOS/partida.o OBJETOS/menus.o OBJETOS/varias.o OBJETOS/jugadas.o OBJETOS/informes.o OBJETOS/ranking.o OBJETOS/franjas.o

OBJETOS/mainMaster.o: main/mainMaster.c main/menus.h main/varias.h
	gcc -Wall -c -o OBJETOS/mainMaster.o main/mainMaster.c

OBJETOS/config.o: Config/config.c Config/config.h
	gcc -Wall -c -o OBJETOS/config.o Config/config.c

OBJETOS/partida.o: Juego/partida.c Config/config.h Juego/partida.h Juego/jugadas.h Tiempo/tiempos.h Informes/ranking.h
	gcc -Wall -c -o OBJETOS/partida.o Juego/partida.c

OBJETOS/jugadas.o: Juego/jugadas.c Juego/jugadas.h
	gcc -Wall -c -o OBJETOS/jugadas.o Juego/jugadas.c

OBJETOS/menus.o: main/menus.c Juego/jugadas.h Config/config.h Juego/partida.h main/menus.h main/varias.h Informes/ranking.h
	gcc -Wall -c -o OBJETOS/menus.o main/menus.c

OBJETOS/varias.o: main/varias.c main/varias.h
	gcc -Wall -c -o OBJETOS/varias.o main/varias.c

OBJETOS/tiempos.o: Tiempo/tiempos.c Tiempo/tiempos.h
	gcc -Wall -c -o OBJETOS/tiempos.o Tiempo/tiempos.c

OBJETOS/informes.o: Informes/informes.c Informes/informes.h Juego/jugadas.h Informes/franjas.h
	gcc -Wall -c -o OBJETOS/informes.o Informes/informes.c

OBJETOS/ranking.o: Informes/ranking.c Informes/ranking.h
	gcc -Wall -c -o OBJETOS/ranking.o Informes/ranking.c

OBJETOS/franjas.o: Informes/franjas.c Informes/franjas.h Juego/jugadas.h Tiempo/tiempos.h
	gcc -Wall -c -o OBJETOS/franjas.o Informes/franjas.c

clean:
	del OBJETOS\mainMaster.o OBJETOS\config.o OBJETOS\partida.o OBJETOS\menus.o OBJETOS\varias.o OBJETOS\jugadas.o OBJETOS\tiempos.o OBJETOS\informes.o OBJETOS\ranking.o OBJETOS\franjas.o
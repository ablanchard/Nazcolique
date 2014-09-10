CC= gcc
FLAGS= -lSDL -lSDLmain -lSDL_image -Wall

all: Nazcolique

Nazcolique : main.o game.o edit.o client.o serveur.o crypt.o loading.o menu.o attaque.o move.o col.o event.o
	$(CC) -o Nazcolique main.o game.o edit.o client.o serveur.o crypt.o loading.o menu.o attaque.o move.o col.o event.o $(FLAGS) -pthread
main.o: main.c cons.h game.h edit.h
	$(CC) -c main.c $(FLAGS)
game.o: game.c cons.h game.h edit.h
	$(CC) -c game.c $(FLAGS)
edit.o: edit.c cons.h game.h edit.h
	$(CC) -c edit.c $(FLAGS)
client.o: client.c
	$(CC) -c client.c -pthread -o client.o
serveur.o: serveur.c
	$(CC) -c serveur.c -o serveur.o
crypt.o: crypt.c
	$(CC) -c crypt.c -o crypt.o
loading.o: loading.c
	$(CC) -c loading.c -o loading.o
menu.o: menu.c
	$(CC) -c menu.c -o menu.o
attaque.o: attaque.c
	$(CC) -c attaque.c -o attaque.o
move.o: move.c
	$(CC) -c move.c -o move.o
col.o: col.c
	$(CC) -c col.c -o col.o
event.o: event.c
	$(CC) -c event.c -o event.o

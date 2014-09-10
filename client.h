#include "cons.h"
#include "game.h"
#include "serveur.h"
#include "crypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void* get_in_addr(struct sockaddr *sa);
int get_in_port (struct sockaddr *sa);
int connect_tcp (char* adresse);//Se connecte en TCp a l'adresse donne puis retourne le numero de socket
void envoi_message (int sock, int touche);
void remplir_struct (char* m, sdl_c *map);
void* client (sdl_c *map);

int socktcp;
int bool_client;

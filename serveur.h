
#include "cons.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define PORT "9999" // port we're listening on
#define UDPPORT 9999

void message_unload_pnj(int i);
void message_load_pnj(sdl_c *map);
void actualisation_jserveur (sdl_c *map);
void actualisation_pnj (sdl_c *map);
void actualisation_pj (sdl_c *map);
void creation_message_pnj(sdl_c *map,char *m,int d,int f);

void raz (char *m, int i);
void traiter_requete (int desc , char* message, int* table_pseudo,sdl_c *map);
void creation_message (int ID,sdl_c *map,char* m);
void analyse_ordre(int ID, sdl_c *map, char* m);
void *get_in_addr (struct sockaddr *sa);
int get_in_port (struct sockaddr *sa);
void* serveur (sdl_c *map);

int sockbcast;
struct sockaddr_in their_addr;

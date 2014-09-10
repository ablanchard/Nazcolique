//#include "game.h"
#include "client.h"
#include "cons.h"




int load_pnj(sdl_c* map,char* stat,int d,int nb);
void load_pj(sdl_c* map, FILE* f,int i);
void unload_pj (sdl_c *map, int i);
void unload_pnj (sdl_c *map, int i);
void load_m(sdl_c* map,const char* nom_m);
void allocation_pers (sdl_c* map);
void charger_pnj (sdl_c *map,char *conf);


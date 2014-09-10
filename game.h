#ifndef DEF_SDL
#define DEF_SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif
#include "cons.h"
#ifndef DEF_GAME
#define DEF_GAME

typedef struct PERS
{
	char map[TAILLE_NOM];
	char nom[TAILLE_NOM];
	SDL_Rect pos;
	SDL_Rect sprite;
	SDL_Surface* pic;
	SDL_Surface* atk;
	int ok;
	int pos_s; // Entier qui determine quel sprite doit être utilise pour le personnage en question, sur une image avec 8 sprites :
	/*
	0 2 4 6
	1 3 5 7
	*/
	int att;//Booleen indiquant si le pers attaque ou non
	int deg;//nombre de degats qu'il inflige
	int pv;//Nombre de point de vie
	int sens;
	int pv_m;
	int xp;
	int v_move;
 //vitesse de mouvement en ms, chaque changement de case prend v_move ms DOIT ETRE MULTIPLE DE 3
	int ldv; //Rayon en pixels du champ de vision
}pers;

typedef struct DIF_p
{
	int x; 
	int y;
	int dis;
}dif_p;


typedef struct SDL_m
{
	int m; // i = 0 menu désactivé, i = 1 menu activé (compatibilité affichage blit_a)
	int choice;
	SDL_Surface* menu; // Fond du menu
	SDL_Surface* menu_c[NB_CHOICE_MENU]; // Fond de selection du menu
	SDL_Surface* menu_m; // Choix du menu
	SDL_Rect posm; // Rect de pos du menu
}sdl_m;

typedef struct SDL_i
{
	SDL_Surface* inte; // Image de l'interface
	SDL_Rect posi; // Rect de inte
}sdl_i;

typedef struct SDL_c
{
	SDL_Surface* wmain;
	SDL_Surface* map;
	SDL_Rect posm; // Rect de map
        SDL_Rect pv_r;
        SDL_Rect pv_s;
        SDL_Surface pv_i;
        SDL_Surface pv_m;
        SDL_Surface deg_i;
	pers* tab[NB_PERS_MAP]; // Tableau qui contient tous les personnages connectés et sur la map;
	pers* tac[NB_PNJ_MAX]; // Tableau qui contient tous les personnages non joueurs de la map affichée;
	int nb_pj; // Nombre de personnages joueurs connectés (affichage prioritaire) de la map
	// LE PERSONNAGE DU JOUEUR DU PROGRAMME EST TOUJOURS EN 0 (Pour apparaitre par dessus les autres personnages)
	int nb_pnj;
	int vague;
	sdl_m* mmain;
	sdl_i* imain;
	SDL_Event event; // Gestion des evenements du joueur principal
}sdl_c;


void interface (sdl_c *map,int n);
void game(sdl_c* map); //La fonction gere le jeu globalement
//int wmenu(sdl_c* map); //Gere le menu d'options
//int event_p(sdl_c* map); //Gere les appuis de touches sur le clavier
//int event_p_net(sdl_c* map); //Gere les appuis de touches sur le clavier
//int mmenu(sdl_c* map); //Gere le menu d'options
//void move_p_net (sdl_c *map,int p);
//void move_p(sdl_c* map, int p); //Gere les modifications de la structure pers au niveau des mouvements
//void move_ap(sdl_c* map,int p); //Gere les modifications de la structure pers au niveau des combats
//void move_ac(sdl_c* map, int p); //Cf ci dessus pour les pnjs
Uint32 blit_a(Uint32 intervalle , void* parametre); //Affiche a intervalles de TIME ms les surfaces blittées
//void load_m(sdl_c* map, const char* nom_m); //Charge la map nom_m en mémoire
//void load_pj(sdl_c* map, FILE* f, int i); //Charge le personnage issu de FILE en memoire, si f = NULL charge un pers test
//void unload_pj (sdl_c *map, int i);
//int load_pnj(sdl_c* map,int type,int d,int nb); //Charge les pnjs de la map courante
void norme(pers* a, pers* b,dif_p* k); // Rempli k avec la distance en pixels sur l'axe x et y et la distance entre eux
//void col_c(sdl_c* map, int p);
//void col_p(sdl_c* map, int p);
//void atk_c(sdl_c* map, int p, SDL_Rect* atk_s);
//void atk_p(sdl_c* map, int p, SDL_Rect* atk_s);
void kill_pj(sdl_c* map, int p);
void kill_pnj(sdl_c* map, int p);
void spawn_pnj(sdl_c* map);
//void move_pnj(sdl_c* map);
int (*event) (sdl_c *);
void (* move_PNJ) (sdl_c*);
int n_player;
int w_pause;
int ok;
//void move_c(sdl_c* map, int p);
//void move_c_net(sdl_c* map, int p);
//void allocation_pers(sdl_c *map);

#endif


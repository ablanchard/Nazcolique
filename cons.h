/*
   Fichier regroupant les constantes.
*/

#ifndef DEF_CONS
#define DEF_CONS

#define TAILLE_PIX 24 // Taille d'un sprite en pixels (Dois être multiple de 6) 
#define PERS_PIX 32 // Hauteur d'un sprite de personnage en pixels 
#define TAILLE_NOM 20 // Taille des noms de personnages et des maps qen caracteres
/*
   Un personnage prend un sprite et demi : 24 * 32 (Il recouvre le sprite du dessus en partie).
*/
#define TIME 40 // 20 ms => 50 FPS
#define RES_X 1024
#define RES_Y 768
#define RES_I 256 // Largeur de l'interface en pixels
#define NB_COLOR 32
#define NB_CHOICE_MENU 5 // En partant de 0
#define NB_PERS_MAP 12
#define NB_PNJ_MAX 300
// Jouer Solo/ Heberger Partie/ Rejoindre Partie/ Editer Carte/ Changer Sprite/
enum {UP, RIGHT, DOWN, LEFT, SPACE};

#define PORT "9999"
#define MAXDATASIZE 128

#endif
/* Pointeur sur fontcions */


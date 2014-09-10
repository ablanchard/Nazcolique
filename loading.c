#include "loading.h"


int load_pnj(sdl_c* map,char *stat,int d,int nb)
{//Rempli la struct map->tac de nb pnj de type type a partir de la case d
        int i=0;
	int type,deg,ldv,pv;
	int j=1;
	char buf[8];
	type=stat[0]-48;
	printf("%i \n",type);
	for (j=1;j<4;j++)
		buf[j-1]=stat[j];
	buf[j-1]='\0';
	pv=atoi(buf);
	for (j=4;j<6;j++)
		buf[j-4]=stat[j];
	buf[j-4]='\0';
	deg=atoi(buf);
	for (j=6;j<9;j++)
		buf[j-6]=stat[j];
	buf[j-6]='\0';
	ldv=atoi(buf);
        for(i=d;i<d+nb;i++)
        {
                printf("Loading pnj n°%i %i\n",i,type);
                pers* hero=(pers*)malloc(sizeof(pers));
                map->tac[i]=hero;
                hero->pic = IMG_Load("./images/sprite2.png");
                hero->sens=DOWN;
                strcpy(hero->nom,"Soldat");
                hero->sprite.x=24;
                hero->sprite.y=0;
                if (type==-1)
                        hero->pos_s=rand()%8;
                else
                        hero->pos_s=type;
                hero->att=0;
                hero->deg=deg;
                hero->pv=pv;
                hero->sprite.w=TAILLE_PIX;
                hero->sprite.h=PERS_PIX;
                hero->pos.x=rand()%350+274;
                hero->pos.y=rand()%350+118;
                hero->v_move=5;
                hero->ldv=ldv;
		hero->atk=IMG_Load("./images/slash.png");
                printf("Loading pnj n°%i done\n",i);
        }
        return i;
}

void load_pj(sdl_c* map, FILE* f,int i)
{
        printf("Loading joueur %i\n",i);
        if(f==NULL)
        {
                pers* hero=(pers*)malloc(sizeof(pers));
                map->tab[i]=hero;
                hero->pic = IMG_Load("./images/sprite.png");
                hero->sens=DOWN;
                strcpy(hero->nom,"Grumeloche");
                hero->sprite.x=24;
                hero->sprite.y=0;
                hero->pos_s=0;
                hero->deg=5;
		hero->ok=1;
                hero->pv=100;
		hero->pv_m=100;
		hero->xp=0;
                hero->att=0;
                hero->sprite.w=TAILLE_PIX;
                hero->sprite.h=PERS_PIX;
                hero->pos.x=rand()%100+256;
                hero->pos.y=rand()%100;
                hero->v_move=10;
                hero->atk=IMG_Load("./images/slash.png");
        }
        else
        {
                //######################## A MODIFIER PLUS TARD POUR LIRE DEPUIS UN FICHIER OU VIA SOCKET
        }
}

void unload_pj (sdl_c *map, int i)
{
        printf("Unload perso n°%i\n",i);
                pers* ancien=map->tab[map->nb_pj-1];
                pers* hero=map->tab[i];
                hero->pic = IMG_Load("./images/sprite.png");
                hero->sens=ancien->sens;
                strcpy(hero->nom,"Grumeloche");
                hero->sprite.x=ancien->sprite.x;
                hero->sprite.y=ancien->sprite.y;
                hero->pos_s=ancien->pos_s;
                hero->sprite.w=TAILLE_PIX;
                hero->sprite.h=PERS_PIX;
                hero->pos.x=ancien->pos.x;
                hero->pos.y=ancien->pos.y;
		hero->ok=ancien->ok;
                hero->v_move=ancien->v_move;
                hero->atk=IMG_Load("./images/slash.png");
                hero->pv=ancien->pv;
                hero->deg=ancien->deg;
                hero->att=ancien->att;
        map->nb_pj--;
	free(ancien);
        printf("Unload terminé\n");
}

void unload_pnj (sdl_c *map, int i)
{
        printf("Unload pnj n°%i\n",i);
                pers* ancien=map->tac[map->nb_pnj-1];
                pers* hero=map->tac[i];
                hero->pic = IMG_Load("./images/sprite2.png");
                hero->sens=ancien->sens;
                strcpy(hero->nom,"Grumeloche");
                hero->sprite.x=ancien->sprite.x;
                hero->sprite.y=ancien->sprite.y;
                hero->pos_s=ancien->pos_s;
                hero->sprite.w=TAILLE_PIX;
                hero->sprite.h=PERS_PIX;
                hero->pos.x=ancien->pos.x;
                hero->pos.y=ancien->pos.y;
                hero->v_move=ancien->v_move;
                hero->atk=IMG_Load("./images/slash.png");
                hero->pv=ancien->pv;
                hero->deg=ancien->deg;
                hero->att=ancien->att;
        map->nb_pnj--;
	free(ancien);
        printf("Unload terminé\n");
}

void load_m(sdl_c* map,const char* nom_m)
{
        map->map=IMG_Load(nom_m);
}

void allocation_pers (sdl_c* map)
{
        int i=0;
        for (i=0;i<map->nb_pj;i++)
                load_pj(map,NULL,i);
	printf("PJ chargé\n");
	if (bool_client)
        	load_pnj(map,"101005200",0,map->nb_pnj);//Rempli toute la struct map->tac de pnj aleatoire
        else
		charger_pnj (map,"pnj.conf");
}

void charger_pnj (sdl_c *map,char *conf)
{//Charge les pnj en fonction de la vague choisie
FILE *fic=fopen(conf,"r");
if (fic!=NULL)
	printf("Fichier de configuration %s ouvert\n",conf);
char* stat=(char*)calloc(16,sizeof(char));
fgets(stat,16,fic);
stat[9]='\0';
int vague=map->vague;
int nb_type=(vague+1)/2;
if (nb_type > 7)
	nb_type=7;
int i=1;
int debut=0;
int nb_pnj=(2+vague)*map->nb_pj;
int nb_tot_pnj=0;
for (i=1;i<=nb_type;)
{
	printf("Chargement des persos de type %i\n",i);
        if (nb_tot_pnj+nb_pnj>=NB_PNJ_MAX)
                nb_pnj=0;
        debut=load_pnj(map,stat,debut,nb_pnj);
        nb_tot_pnj=nb_tot_pnj+nb_pnj;
        i++;
	fgets(stat,16,fic);
	stat[9]='\0';
        nb_pnj=(vague-i*2+2)*map->nb_pj;
}
printf("Chargement des pnj terminé\n");
fclose(fic);
free(stat);
map->nb_pnj=nb_tot_pnj;
}


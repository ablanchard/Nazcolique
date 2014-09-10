//#include "cons.h"
//#include "game.h"
#include "edit.h"
#include "client.h"
#include "move.h"
#include "event.h"
#include "loading.h"
#include "menu.h"
#include <pthread.h>
#ifndef DEF_SDL
#define DEF_SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char** argv)
{
	SDL_Surface* wmain;
	int test = 1;
	char adresse[32];
	char adresse_bcast[32];
	char adresse_host[32];
	char interface[32];
	bool_client=0;
	int nb_pnj=10;
	int i;
	int vague=1;
	ok=1;
	if (argc>=2)
	{
		if (argc==2)
		{
			if ((strcmp(argv[1],"-pnj")!=0)&&(strcmp(argv[1],"-host")!=0)&&(strcmp(argv[1],"-bcast")!=0)&&(strcmp(argv[1],"-i")!=0))
				strcpy(adresse,argv[1]);
			else
			{
				printf("usage : ./Nazcolique %s PARAMETRE\n",argv[1]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			for (i=1;i<argc;i++)
			{
				if (i+1>=argc)
				{
					printf("usage : ./Nazcolique %s PARAMETRE\n",argv[i]);
					exit(EXIT_FAILURE);
				}
				else
				{
					if (strcmp(argv[i],"-pnj")==0)
						nb_pnj=atoi(argv[i+1]);
					else
					{
						if (strcmp(argv[i],"-host")==0)
							strcpy(adresse_host,argv[i+1]);
						else
						{	
							if (strcmp(argv[i],"-bcast")==0)
								strcpy(adresse_bcast,argv[i+1]);
							else
							{
								if (strcmp(argv[i],"-i")==0)
									strcpy(interface,argv[i+1]);
								else
								{
									if (strcmp(argv[i],"-v")==0)
										vague=atoi(argv[i+1]);
									else
										strcpy(adresse,argv[i]);
								}
							}
						}
					}
				}
				i++;
			}
		}
	}
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		perror("SDL INIT FAIL : \n");
		exit(EXIT_FAILURE);
	}

	if((wmain = SDL_SetVideoMode(RES_X,RES_Y,NB_COLOR, SDL_NOFRAME | SDL_HWSURFACE | SDL_DOUBLEBUF
//  | SDL_FULLSCREEN
)) == NULL)
	{
		perror("SDL SETVIDEO MODE FAIL :\n");
		exit(EXIT_FAILURE);
	}

	SDL_EnableKeyRepeat(200, 100);

	SDL_WM_SetIcon(IMG_Load("./images/logo.bmp"), NULL);
	SDL_WM_SetCaption("Nazekolique","Nazekolique");

	SDL_Surface* menu = IMG_Load("./images/menu.bmp");

	SDL_Surface* menu_c[NB_CHOICE_MENU];
	menu_c[0] = IMG_Load("./images/menu_0.png");
	menu_c[1] = IMG_Load("./images/menu_1.png");
	menu_c[2] = IMG_Load("./images/menu_2.png");
	menu_c[3] = IMG_Load("./images/menu_3.png");
	menu_c[4] = IMG_Load("./images/menu_4.png");

	SDL_Surface* menu_m = IMG_Load("./images/menu_m.png");

	sdl_m mmain;
	mmain.menu=menu;

	for(test=0;test<NB_CHOICE_MENU;test++)
		mmain.menu_c[test]=menu_c[test];

	mmain.menu_m=menu_m;
	mmain.posm.x=(int)((RES_X-384)/2);
	mmain.posm.y=(int)((RES_Y-700)/2);
	mmain.m=0;
	mmain.choice=0;

	sdl_i imain;
	imain.inte=IMG_Load("./images/interface.png");
	imain.posi.x=0;
	imain.posi.y=0;

	sdl_c map;
	map.mmain=&mmain;
	map.imain=&imain;
	map.wmain =wmain;
	map.map=IMG_Load("./images/fondvert.png");
	map.posm.x=256;
	map.posm.y=0;
	pthread_t th;
        map.pv_i=*IMG_Load("./images/pvbar.png");
        map.pv_m=*IMG_Load("./images/pv2bar.png");
        map.deg_i=*IMG_Load("./images/degbar.png");
        map.pv_r.x=24;
        map.pv_r.y=32;
        map.pv_r.w=100;
        map.pv_r.h=24;

        map.pv_s.x=0;
        map.pv_s.y=0;
        map.pv_s.w=100;
        map.pv_s.h=24;

	for(test=0;test<NB_PERS_MAP;test++)
	{
		map.tab[test]=NULL;
		map.tac[test]=NULL;
	}
	event=&event_p;
	move_PNJ=&move_pnj;
	sockbcast=0;
	map.nb_pj=1;
	map.vague=vague;
	n_player=0;
	while (1)
	{
		map.mmain->choice = mmenu(&map);
		switch(map.mmain->choice)
		{
			case 4:
				exit(EXIT_SUCCESS);
				break;
			case 0:
				//map.nb_pnj=nb_pnj;
				game(&map);
				break;
			case 1://Héberger une partie
				//bool_client=1;
				printf("Initialisation de la connection wait\n");
				//allocation_pers(&map);	
				if (pthread_create (&th, NULL, serveur,(void *)&map)<0)//on lance le serveur dans un thread
				{
					fprintf (stderr,"pthread_create error for thread 2\n");
					exit(EXIT_FAILURE);
				}
				//map.nb_pnj=nb_pnj;
				game(&map);
				break;
			case 2://Rejoindre une partie
				map.nb_pnj=0;
				printf("Connexion réalisé\n");
				event=&event_p_net;
				move_PNJ=NULL;
				bool_client=1;
				printf("Initialisation de la connection wait\n");
				load_m(&map,"./images/fondvert.png");
				//map.nb_pnj=1;
				//allocation_pers(&map);
				if (pthread_create (&th, NULL, client,&map)<0)
				{
					fprintf (stderr,"pthread_create error for thread 2\n");
					exit(EXIT_FAILURE);
				}
				if ( (socktcp=connect_tcp(adresse))<3)
				{
					perror("Erreur de connection TCP");
					exit(EXIT_FAILURE);
				}
				sleep(1);
				game(&map);
				break;

		}
	}
}

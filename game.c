#include "loading.h"
#include "menu.h"
#include "col.h"
#include "attaque.h"
#include "move.h"
#include "event.h"
#include "edit.h"

#ifndef DEF_SDL
#define DEF_SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#endif

#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


Uint32 blit_a(Uint32 intervalle, void* parametre)
{
        sdl_c* map=parametre;
        int i;
        SDL_Rect atk_s;
        atk_s.w=TAILLE_PIX;
        atk_s.h=TAILLE_PIX;
        atk_s.y=0;

        SDL_BlitSurface(map->map,NULL,map->wmain,&map->posm);
        SDL_BlitSurface(map->imain->inte,NULL,map->wmain,&map->imain->posi);
	if (ok==1&&(TIME*w_pause)>=3000)
	{
		if (!bool_client)
			move_pnj(map);
		i=0;
		while(i<map->nb_pnj)
		{
			if(map->tac[i]->pv > 0)
			{
				SDL_BlitSurface(map->tac[i]->pic,&map->tac[i]->sprite,map->wmain,&map->tac[i]->pos);
				atk_c(map,i,&atk_s);
			}
			else
			{
				if (!bool_client) 
					kill_pnj(map,i);
			}
			i++;
		}
	}

        for(i=map->nb_pj-1;i>=0;i--)
        {
                if(map->tab[i]->pv > 0)
                {
                        SDL_BlitSurface(map->tab[i]->pic,&map->tab[i]->sprite,map->wmain,&map->tab[i]->pos);
                        atk_p(map,i,&atk_s);
                }
                else
		{
			if (!bool_client)
			 	kill_pj(map,i);
		}
        }
	/*
        if(map->tab[0]->pv > 0)
        {
                SDL_BlitSurface(map->tab[0]->pic,&map->tab[0]->sprite,map->wmain,&map->tab[0]->pos);
                atk_p(map,0,&atk_s);
        }
        else
                        kill_pj(map,0);*/
        interface(map,n_player);


        if(map->mmain->m == 1)
        {
                SDL_BlitSurface(map->mmain->menu,NULL,map->wmain,&map->mmain->posm);
                SDL_BlitSurface(map->mmain->menu_c[map->mmain->choice],NULL,map->wmain,&map->mmain->posm);
                SDL_BlitSurface(map->mmain->menu_m,NULL,map->wmain,&map->mmain->posm);
        }
        SDL_Flip(map->wmain);
	
	if (map->nb_pnj==0)
	{
		ok=0;
		for(i=0;i<map->nb_pj-1;i++)
			map->tab[i]->ok=0;
		w_pause=0;
		if (!bool_client)
			spawn_pnj(map);
		map->tab[0]->ok=1;
	}
	if (ok==0)
	{
		ok=1;
		for(i=0;i<map->nb_pj-1;i++)
			ok=ok*map->tab[i]->ok;
	}
	w_pause++;// */
        return intervalle;
}


void interface(sdl_c* map,int n)
{
        map->pv_r.y = 32;
        map->pv_s.w = map->tab[n]->pv;
        SDL_BlitSurface(&map->pv_i,&map->pv_s,map->wmain,&map->pv_r);
        map->pv_s.w = map->tab[n]->pv_m;
        map->pv_r.y = 140;
        SDL_BlitSurface(&map->pv_m,&map->pv_s,map->wmain,&map->pv_r);
        map->pv_s.w = map->tab[n]->deg;
        map->pv_r.y = 235;
        SDL_BlitSurface(&map->deg_i,&map->pv_s,map->wmain,&map->pv_r);
}

void spawn_pnj(sdl_c* map)
{
map->vague++;
charger_pnj(map,"pnj.conf");
message_load_pnj(map);
}

void kill_pj(sdl_c* map, int p)
{
        map->tab[p]->pv=100;
        map->tab[p]->pos.x = RES_I+rand()%40;
        map->tab[p]->pos.y = PERS_PIX+rand()%40;
        map->tab[p]->deg=5;
        map->tab[p]->pv_m=100;
        map->tab[p]->xp=0;
	actualisation_pj(map);
}

void kill_pnj(sdl_c* map, int p)
{
message_unload_pnj(p);
unload_pnj(map,p);
}

void lvl_up(sdl_c* map, int p)
{
        if(map->tab[p]->xp > (int)(exp((double)((map->tab[p]->deg-5)/2)))) //croissance expo de l'xp necessaire pour lvl up
        {
                map->tab[p]->deg++;
                map->tab[p]->pv_m=map->tab[p]->pv_m+5;
                map->tab[p]->pv=map->tab[p]->pv_m;
        }
}

void game(sdl_c* map)
{
	if (!bool_client)
	{
		load_m(map,"./images/fondvert.png");
		allocation_pers(map);
	}
	w_pause=1000;
	ok=1;
	SDL_TimerID timer;
	printf("Lancement de l'interface graphique\n");
	timer = SDL_AddTimer(TIME, blit_a, map);
	printf("timer=%i\n",timer);
	event(map);
}



void norme(pers* a, pers* b, dif_p* k)
{
	k->x=a->pos.x-b->pos.x;
	k->y=a->pos.y-b->pos.y;
	k->dis=abs( (int) sqrt( (double) ((k->x)*(k->x) + (k->y)*(k->y) ) ) );
}



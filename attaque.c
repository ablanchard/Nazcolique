
#include "attaque.h"

void atk_c(sdl_c* map, int p, SDL_Rect* atk_s)
{
        if(map->tac[p]->att == 1)
        {
                switch(map->tac[p]->sens)
                {
                        case LEFT:
                                atk_s->x=TAILLE_PIX*LEFT;
                                map->tac[p]->pos.x = map->tac[p]->pos.x - TAILLE_PIX;
                                SDL_BlitSurface(map->tac[p]->atk,atk_s,map->wmain,&map->tac[p]->pos);
                                move_ac(map,p);
                                map->tac[p]->pos.x = map->tac[p]->pos.x + TAILLE_PIX;
                                break;
                        case RIGHT:
                                atk_s->x=TAILLE_PIX*RIGHT;
                                map->tac[p]->pos.x = map->tac[p]->pos.x + TAILLE_PIX;
                                SDL_BlitSurface(map->tac[p]->atk,atk_s,map->wmain,&map->tac[p]->pos);
                                move_ac(map,p);
                                map->tac[p]->pos.x = map->tac[p]->pos.x - TAILLE_PIX;
                                break;
                        case DOWN:
                                atk_s->x=TAILLE_PIX*DOWN;
                                map->tac[p]->pos.y = map->tac[p]->pos.y + TAILLE_PIX;
                                SDL_BlitSurface(map->tac[p]->atk,atk_s,map->wmain,&map->tac[p]->pos);
                                move_ac(map,p);
                                map->tac[p]->pos.y = map->tac[p]->pos.y - TAILLE_PIX;
                                break;
                        case UP:
                                atk_s->x=TAILLE_PIX*UP;
                                map->tac[p]->pos.y = map->tac[p]->pos.y - TAILLE_PIX;
                                SDL_BlitSurface(map->tac[p]->atk,atk_s,map->wmain,&map->tac[p]->pos);
                                move_ac(map,p);
                                map->tac[p]->pos.y = map->tac[p]->pos.y + TAILLE_PIX;
                                break;
                }
        }
        map->tac[p]->att = 0;
}
void atk_p(sdl_c* map, int p, SDL_Rect* atk_s)
{
        if(map->tab[p]->att == 1 )
        {
                switch(map->tab[p]->sens)
                {
                        case LEFT:
                                atk_s->x=TAILLE_PIX*LEFT;
                                map->tab[p]->pos.x = map->tab[p]->pos.x - TAILLE_PIX;
                                SDL_BlitSurface(map->tab[p]->atk,atk_s,map->wmain,&map->tab[p]->pos);
                                move_ap(map,p);
                                map->tab[p]->pos.x = map->tab[p]->pos.x + TAILLE_PIX;
                                break;
                        case RIGHT:
                                atk_s->x=TAILLE_PIX*RIGHT;
                                map->tab[p]->pos.x = map->tab[p]->pos.x + TAILLE_PIX;
                                SDL_BlitSurface(map->tab[p]->atk,atk_s,map->wmain,&map->tab[p]->pos);
                                move_ap(map,p);
                                map->tab[p]->pos.x = map->tab[p]->pos.x - TAILLE_PIX;
                                break;
                        case DOWN:
                                atk_s->x=TAILLE_PIX*DOWN;
                                map->tab[p]->pos.y = map->tab[p]->pos.y + TAILLE_PIX;
                                SDL_BlitSurface(map->tab[p]->atk,atk_s,map->wmain,&map->tab[p]->pos);
                                move_ap(map,p);
                                map->tab[p]->pos.y = map->tab[p]->pos.y - TAILLE_PIX;
                                break;
                        case UP:
                                atk_s->x=TAILLE_PIX*UP;
                                map->tab[p]->pos.y = map->tab[p]->pos.y - TAILLE_PIX;
                                SDL_BlitSurface(map->tab[p]->atk,atk_s,map->wmain,&map->tab[p]->pos);
                                move_ap(map,p);
                                map->tab[p]->pos.y = map->tab[p]->pos.y + TAILLE_PIX;
                                break;
                }
        }
        map->tab[p]->att = 0;
}
void move_ap(sdl_c* map, int p)
{
        int i;

        for(i=0;i<map->nb_pj;i++)
        {
                if(i!=p)
                {
                        // CELUI QUI BOUGE X CELUI QUI NE BOUGE PAS
                        if((map->tab[p]->pos.x < map->tab[i]->pos.x + TAILLE_PIX)      // trop à droite
                                        && (map->tab[p]->pos.x + TAILLE_PIX > map->tab[i]->pos.x) // trop à gauche
                                        && (map->tab[p]->pos.y < map->tab[i]->pos.y + TAILLE_PIX) // trop en bas
                                        && (map->tab[p]->pos.y + TAILLE_PIX > map->tab[i]->pos.y)
                                        && (map->tab[p]->pv > 0))
                        {//COLLISION ON FRAPPE
                                map->tab[i]->pv = map->tab[i]->pv - map->tab[p]->deg;
                        }
                }
        }

        for(i=0;i<map->nb_pnj;i++)
        {
                if((map->tab[p]->pos.x < map->tac[i]->pos.x + TAILLE_PIX) // trop à droite 
                                && (map->tab[p]->pos.x + TAILLE_PIX > map->tac[i]->pos.x) // trop à gauche
                                && (map->tab[p]->pos.y < map->tac[i]->pos.y + TAILLE_PIX) // trop en bas
                                && (map->tab[p]->pos.y + TAILLE_PIX > map->tac[i]->pos.y)//##### +/- 3 Permet de faire le tour d'un autre pnj sans trop de soucis
                                && (map->tab[p]->pv > 0))
                {//COLLISION ON FRAPPE
                        map->tac[i]->pv = map->tac[i]->pv - map->tab[p]->deg;
                        if(map->tac[i]->pv < 0)
                                {
                                map->tab[p]->xp=map->tab[p]->xp+1+map->tac[i]->pos_s;
                                lvl_up(map,p);
                                }
                }
        }
}

void move_ac(sdl_c* map, int p)
{
        int i;

        for(i=0;i<map->nb_pj;i++)
        {
                if((map->tac[p]->pos.x < map->tab[i]->pos.x + TAILLE_PIX)      // trop à droite
                                && (map->tac[p]->pos.x + TAILLE_PIX > map->tab[i]->pos.x) // trop à gauche
                                && (map->tac[p]->pos.y < map->tab[i]->pos.y + TAILLE_PIX) // trop en bas
                                && (map->tac[p]->pos.y + TAILLE_PIX > map->tab[i]->pos.y)
                                        && (map->tac[p]->pv > 0))
                {//COLLISION ON RECULE

                        map->tab[i]->pv = map->tab[i]->pv - map->tac[p]->deg;
                        if(i==0)
                        map->pv_r.w = map->tab[0]->pv;
                }
        }

        for(i=0;i<map->nb_pnj;i++)
        {
                if(i!=p)
                {
                        if((map->tac[p]->pos.x < map->tac[i]->pos.x + TAILLE_PIX) // trop à droite 
                                        && (map->tac[p]->pos.x + TAILLE_PIX > map->tac[i]->pos.x) // trop à gauche
                                        && (map->tac[p]->pos.y < map->tac[i]->pos.y + TAILLE_PIX) // trop en bas
                                        && (map->tac[p]->pos.y + TAILLE_PIX > map->tac[i]->pos.y)
                                        && (map->tac[p]->pv > 0))
                        {//COLLISION ON RECULE
                                map->tac[i]->pv = map->tac[i]->pv - map->tac[p]->deg;
                        }
                }
        }
}


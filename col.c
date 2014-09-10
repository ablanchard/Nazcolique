#include "col.h"

void col_p(sdl_c* map, int p)
{
        int i;

        for(i=0;i<map->nb_pj;i++)
        {
                if(i!=p)
                {
                        if((map->tab[p]->pos.x < map->tab[i]->pos.x + TAILLE_PIX - 3)      // trop à droite
                                        && (map->tab[p]->pos.x + TAILLE_PIX > map->tab[i]->pos.x + 3) // trop à gauche
                                        && (map->tab[p]->pos.y < map->tab[i]->pos.y + TAILLE_PIX - 3) // trop en bas
                                        && (map->tab[p]->pos.y + TAILLE_PIX > map->tab[i]->pos.y + 3)
                                        && (map->tab[p]->pv > 0))
                        {//COLLISION ON RECULE

                                switch(map->tab[p]->sens)
                                {
                                        case LEFT:
                                                map->tab[p]->pos.x=map->tab[i]->pos.x + TAILLE_PIX;
                                                break;
                                        case RIGHT:
                                                map->tab[p]->pos.x=map->tab[i]->pos.x - TAILLE_PIX;
                                                break;
                                        case DOWN:
                                                map->tab[p]->pos.y=map->tab[i]->pos.y - TAILLE_PIX;
                                                break;
                                        case UP:
                                                map->tab[p]->pos.y=map->tab[i]->pos.y + TAILLE_PIX;
                                                break;
                                }
                        }
                }
        }

        for(i=0;i<map->nb_pnj;i++)
        {
                if((map->tab[p]->pos.x < map->tac[i]->pos.x + TAILLE_PIX - 3) // trop à droite 
                                && (map->tab[p]->pos.x + TAILLE_PIX > map->tac[i]->pos.x + 3) // trop à gauche
                                && (map->tab[p]->pos.y < map->tac[i]->pos.y + TAILLE_PIX - 3) // trop en bas
                                && (map->tab[p]->pos.y + TAILLE_PIX > map->tac[i]->pos.y + 3)//##### +/- 3 Permet de faire le tour d'un autre pnj sans trop de soucis
                          	&& (map->tab[p]->pv > 0))
                {//COLLISION ON RECULE

                        switch(map->tab[p]->sens)
                        {
                                case LEFT:
                                        map->tab[p]->pos.x=map->tac[i]->pos.x + TAILLE_PIX;
                                        break;
                                case RIGHT:
                                        map->tab[p]->pos.x=map->tac[i]->pos.x - TAILLE_PIX;
                                        break;
                                case DOWN:
                                        map->tab[p]->pos.y=map->tac[i]->pos.y - TAILLE_PIX;
                                        break;
                                case UP:
                                        map->tab[p]->pos.y=map->tac[i]->pos.y + TAILLE_PIX;
                                        break;
                        }
                }
        }
}

void col_c(sdl_c* map, int p)
{
        int i;
        for(i=0;i<map->nb_pj;i++)
        {
                if((map->tac[p]->pos.x < map->tab[i]->pos.x + TAILLE_PIX - 3)      // trop à droite
                                && (map->tac[p]->pos.x + TAILLE_PIX > map->tab[i]->pos.x + 3) // trop à gauche
                                && (map->tac[p]->pos.y < map->tab[i]->pos.y + TAILLE_PIX - 3) // trop en bas
                                && (map->tac[p]->pos.y + TAILLE_PIX > map->tab[i]->pos.y + 3)
                                        && (map->tac[p]->pv > 0))
                {//COLLISION ON RECULE

                        switch(map->tac[p]->sens)
                        {
                                case LEFT:
                                        map->tac[p]->pos.x=map->tab[i]->pos.x + TAILLE_PIX;
                                        break;
                                case RIGHT:
                                        map->tac[p]->pos.x=map->tab[i]->pos.x - TAILLE_PIX;
                                        break;
                                case DOWN:
                                        map->tac[p]->pos.y=map->tab[i]->pos.y - TAILLE_PIX;
                                        break;
                                case UP:
                                        map->tac[p]->pos.y=map->tab[i]->pos.y + TAILLE_PIX;
                                        break;
                        }
                }
        }
        for(i=0;i<map->nb_pnj;i++)
        {
                if(i!=p)
                {
                        if((map->tac[p]->pos.x < map->tac[i]->pos.x + TAILLE_PIX - 3)      // trop à droite
                                        && (map->tac[p]->pos.x + TAILLE_PIX > map->tac[i]->pos.x + 3) // trop à gauche
                                        && (map->tac[p]->pos.y < map->tac[i]->pos.y + TAILLE_PIX - 3) // trop en bas
                                        && (map->tac[p]->pos.y + TAILLE_PIX > map->tac[i]->pos.y + 3)
                                        && (map->tac[p]->pv > 0))
                        {//COLLISION ON RECULE

                                switch(map->tac[p]->sens)
                                {
                                        case LEFT:
                                                map->tac[p]->pos.x=map->tac[i]->pos.x + TAILLE_PIX;
                                                break;
                                        case RIGHT:
                                                map->tac[p]->pos.x=map->tac[i]->pos.x - TAILLE_PIX;
                                                break;
                                        case DOWN:
                                                map->tac[p]->pos.y=map->tac[i]->pos.y - TAILLE_PIX;
                                                break;
                                        case UP:
                                                map->tac[p]->pos.y=map->tac[i]->pos.y + TAILLE_PIX;
                                                break;
                                }
                        }
                }
        }
}


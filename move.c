#include "move.h"
#include "col.h"
void move_pnj(sdl_c* map)
{
        int i;
        int j;
        dif_p l,k;

        for(i=0;i < map->nb_pnj;i++)
        {
                l.x=0;
                l.y=0;
                l.dis = map->tac[i]->ldv;
                for(j=0;j < map->nb_pj ; j++)
                {
                        norme(map->tac[i],map->tab[j],&k);
                        if(k.dis < l.dis)
                        {
                                l.dis=k.dis;
                                l.x=k.x;
                                l.y=k.y;
                        }
                }
                if(l.dis > PERS_PIX)
                {
                        if(l.x==0 && l.y==0)
                        {
                                if(SDL_GetTicks()%map->nb_pnj == i)
                                {
                                        map->tac[i]->sens=rand()%4;
                                        move_c(map,i);
                                }
                        }
                        else
                        {
                                if( abs(l.x) < abs(l.y) )
                                {
                                        if(l.y > 0)
                                                map->tac[i]->sens=UP;
                                        else
                                                map->tac[i]->sens=DOWN;
}
                                else
                                {
                                        if(l.x > 0)
                                                map->tac[i]->sens=LEFT;
                                        else
                                                map->tac[i]->sens=RIGHT;
                                }
                                move_c(map,i);
                        }
                }
                else
                {
                        map->tac[i]->att = 1;
                }
        }
        actualisation_pnj(map);

}
void move_c(sdl_c* map, int p)
{
        if(map->tac[p]->pos_s%2==0)
                map->tac[p]->sprite.x=map->tac[p]->pos_s/2*TAILLE_PIX*3;
        else
                map->tac[p]->sprite.x=(map->tac[p]->pos_s-1)/2*TAILLE_PIX*3;
        //enum {UP, RIGHT, DOWN, LEFT};
        switch(map->tac[p]->sens)
        {
                case LEFT:
                        if(map->tac[p]->pos.x - map->tac[p]->v_move > RES_I)
                                map->tac[p]->pos.x = map->tac[p]->pos.x - map->tac[p]->v_move;
                        else
                                map->tac[p]->pos.x = RES_I;

                        map->tac[p]->sprite.y=PERS_PIX*(LEFT+4*(map->tac[p]->pos_s%2));
                        break;
                case UP:
                        if(map->tac[p]->pos.y - map->tac[p]->v_move > 0 )
                                map->tac[p]->pos.y = map->tac[p]->pos.y - map->tac[p]->v_move;
                        else
                                map->tac[p]->pos.y = 0;
                        map->tac[p]->sprite.y=PERS_PIX*(UP+4*(map->tac[p]->pos_s%2));
                        break;
                case RIGHT:
                        if(map->tac[p]->pos.x + map->tac[p]->v_move < (RES_X-TAILLE_PIX))
                                map->tac[p]->pos.x = map->tac[p]->pos.x + map->tac[p]->v_move;
                        else
                                map->tac[p]->pos.x = (RES_X-TAILLE_PIX);
                        map->tac[p]->sprite.y=PERS_PIX*(RIGHT+4*(map->tac[p]->pos_s%2));
                        break;
                case DOWN:
                        if(map->tac[p]->pos.y + map->tac[p]->v_move + PERS_PIX < RES_Y)
                                map->tac[p]->pos.y = map->tac[p]->pos.y + map->tac[p]->v_move;
                        else
                                map->tac[p]->pos.y = RES_Y - PERS_PIX;
                        map->tac[p]->sprite.y=PERS_PIX*(DOWN+4*(map->tac[p]->pos_s%2)); // On se met sur la ligne pour sélectionner le sprite
                        break;
                default:
                        break;
        }
        col_c(map,p);
}
void move_c_net(sdl_c* map, int p)
{
        if(map->tac[p]->pos_s%2==0)
                map->tac[p]->sprite.x=map->tac[p]->pos_s/2*TAILLE_PIX*3;
        else
                map->tac[p]->sprite.x=(map->tac[p]->pos_s-1)/2*TAILLE_PIX*3;
        //enum {UP, RIGHT, DOWN, LEFT};
        switch(map->tac[p]->sens)
        {
                case LEFT:
                        map->tac[p]->sprite.y=PERS_PIX*(LEFT+4*(map->tac[p]->pos_s%2));
                        break;
                case UP:
                        map->tac[p]->sprite.y=PERS_PIX*(UP+4*(map->tac[p]->pos_s%2));
                        break;
                case RIGHT:
                        map->tac[p]->sprite.y=PERS_PIX*(RIGHT+4*(map->tac[p]->pos_s%2));
                        break;
                case DOWN:
                        map->tac[p]->sprite.y=PERS_PIX*(DOWN+4*(map->tac[p]->pos_s%2)); // On se met sur la ligne pour sélectionner le sprite
                        break;
                default:
                        break;
        }
}
void move_p_net (sdl_c *map, int p)
{
        if(map->tab[p]->pos_s%2==0)
                map->tab[p]->sprite.x=map->tab[p]->pos_s/2*TAILLE_PIX*3;
        else
                map->tab[p]->sprite.x=(map->tab[p]->pos_s-1)/2*TAILLE_PIX*3;
        //enum {UP, RIGHT, DOWN, LEFT};
        switch(map->tab[p]->sens)
        {
                case LEFT:
                        map->tab[p]->sprite.y=PERS_PIX*(LEFT+4*(map->tab[p]->pos_s%2));
                        break;
                case UP:
                        map->tab[p]->sprite.y=PERS_PIX*(UP+4*(map->tab[p]->pos_s%2));
                        break;
                case RIGHT:
                        map->tab[p]->sprite.y=PERS_PIX*(RIGHT+4*(map->tab[p]->pos_s%2));
                        break;
                case DOWN:
                        map->tab[p]->sprite.y=PERS_PIX*(DOWN+4*(map->tab[p]->pos_s%2)); // On se met sur la ligne pour sélectionner le sprite
                        break;
                default:
                        break;
        }
}
void move_p(sdl_c* map, int p)
{
        if(map->tab[p]->pos_s%2==0)
                map->tab[p]->sprite.x=map->tab[p]->pos_s/2*TAILLE_PIX*3;
        else
                map->tab[p]->sprite.x=(map->tab[p]->pos_s-1)/2*TAILLE_PIX*3;
        //enum {UP, RIGHT, DOWN, LEFT};
        switch(map->tab[p]->sens)
        {
                case LEFT:
                        if(map->tab[p]->pos.x - map->tab[p]->v_move > RES_I)
                                map->tab[p]->pos.x = map->tab[p]->pos.x - map->tab[p]->v_move;
                        else
                                map->tab[p]->pos.x = RES_I;

                        map->tab[p]->sprite.y=PERS_PIX*(LEFT+4*(map->tab[p]->pos_s%2));
                        break;
                case UP:
                        if(map->tab[p]->pos.y - map->tab[p]->v_move > 0 )
                                map->tab[p]->pos.y = map->tab[p]->pos.y - map->tab[p]->v_move;
                        else
                                map->tab[p]->pos.y = 0;
                        map->tab[p]->sprite.y=PERS_PIX*(UP+4*(map->tab[p]->pos_s%2));
                        break;
                case RIGHT:
                        if(map->tab[p]->pos.x + map->tab[p]->v_move < (RES_X-TAILLE_PIX))
                                map->tab[p]->pos.x = map->tab[p]->pos.x + map->tab[p]->v_move;
                        else
                                map->tab[p]->pos.x = (RES_X-TAILLE_PIX);
                        map->tab[p]->sprite.y=PERS_PIX*(RIGHT+4*(map->tab[p]->pos_s%2));
                        break;
                case DOWN:
                        if(map->tab[p]->pos.y + map->tab[p]->v_move + PERS_PIX < RES_Y)
                                map->tab[p]->pos.y = map->tab[p]->pos.y + map->tab[p]->v_move;
                        else
                                map->tab[p]->pos.y = RES_Y - PERS_PIX;
                        map->tab[p]->sprite.y=PERS_PIX*(DOWN+4*(map->tab[p]->pos_s%2)); // On se met sur la ligne pour sélectionner le sprite
                        break;
                default:
                        break;
        }
        col_p(map,p);
}


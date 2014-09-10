
#include "event.h"

int event_p_net (sdl_c *map)
{
        while (1)
        {
                SDL_WaitEvent(&map->event);
                switch(map->event.type)
                {
                        case SDL_QUIT:
                                exit(EXIT_SUCCESS);
                                break;
                        case SDL_KEYDOWN:
                                switch(map->event.key.keysym.sym)
                                {
                                        case SDLK_ESCAPE: // Retourner au menu
                                                wmenu(map);
                                                switch(map->mmain->choice)
                                                {
                                                        case 4:
                                                                exit(EXIT_SUCCESS);
                                                                break;
                                                }
                                                break;
                                        case SDLK_DOWN: // Déplacer vers le bas
                                                envoi_message(socktcp,DOWN);
                                                break;
                                        case SDLK_LEFT: // Déplacer vers la gauche
                                                envoi_message(socktcp,LEFT);
                                                break;
                                        case SDLK_RIGHT: // Déplacer vers la droite
                                                envoi_message(socktcp,RIGHT);
                                                break;
                                        case SDLK_UP: // Déplacer vers le haut
                                                envoi_message(socktcp,UP);
                                                break;
                                        case SDLK_SPACE:
                                                envoi_message(socktcp,SPACE);
                                                break;
                                        default :
                                                break;
                                }
                                break;
                        default :
                                break;
                }
        }
}

int event_p(sdl_c* map)
{
        while (1)
        {
                SDL_WaitEvent(&map->event);
                switch(map->event.type)
                {
                        case SDL_QUIT:
                                exit(EXIT_SUCCESS);
                                break;
                        case SDL_KEYDOWN:
                                switch(map->event.key.keysym.sym)
                                {
                                        case SDLK_ESCAPE: // Retourner au menu
                                                wmenu(map);
                                                switch(map->mmain->choice)
                                                {
                                                        case 4:
                                                                exit(EXIT_SUCCESS);
                                                                break;
                                                }
                                                break;
                                        case SDLK_DOWN: // Déplacer vers le bas
                                                map->tab[0]->sens=DOWN;
                                                move_p(map,0);
                                                actualisation_jserveur(map);
                                                break;
                                        case SDLK_LEFT: // Déplacer vers la gauche
                                                map->tab[0]->sens=LEFT;
                                                move_p(map,0);
                                                actualisation_jserveur(map);
                                                break;
                                        case SDLK_RIGHT: // Déplacer vers la droite
                                                map->tab[0]->sens=RIGHT;
                                                move_p(map,0);
                                                actualisation_jserveur(map);
                                                break;
                                        case SDLK_UP: // Déplacer vers le haut
                                                map->tab[0]->sens=UP;
                                                move_p(map,0);
                                                actualisation_jserveur(map);
                                                break;
                                        case SDLK_SPACE:
                                                map->tab[0]->att=1;
                                                break;
                                        default :
                                                break;
                                }
                                break;
                        default :
                                break;

                }
        }
}


#include "menu.h"

int wmenu(sdl_c* map)
{
        map->mmain->m=1;

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
                                        case SDLK_ESCAPE: // Quitter le menu
                                                map->mmain->choice = 0;
                                                map->mmain->m = 0;
                                                return 0;
                                                break;
                                        case SDLK_DOWN: // Déplacer vers le bas
                                                if(map->mmain->choice >= (NB_CHOICE_MENU - 1))
                                                        map->mmain->choice = 0;
                                                else
                                                        map->mmain->choice++;
                                                break;
                                        case SDLK_UP: // Déplacer vers le haut
                                                if(map->mmain->choice <= 0)
                                                        map->mmain->choice = NB_CHOICE_MENU - 1;
                                                else
                                                        map->mmain->choice--;
                                                break;
                                        case SDLK_RETURN:
                                                map->mmain->m=0;
                                                return 0;
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


int mmenu(sdl_c* map)
{
        int test = 1;
        SDL_Event event;
        SDL_BlitSurface(map->mmain->menu,NULL,map->wmain,&map->mmain->posm);
        SDL_BlitSurface(map->mmain->menu_c[map->mmain->choice],NULL,map->wmain,&map->mmain->posm);
        SDL_BlitSurface(map->mmain->menu_m,NULL,map->wmain,&map->mmain->posm);
        SDL_Flip(map->wmain);

        while (test)
        {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                        case SDL_QUIT:
                                test = 0;
                                break;
                        case SDL_KEYDOWN:
                                switch(event.key.keysym.sym)
                                {
                                        case SDLK_ESCAPE: // Quitter le menu
                                                exit(EXIT_SUCCESS);
                                                break;
                                        case SDLK_DOWN: // Déplacer vers le bas
                                                if(map->mmain->choice == (NB_CHOICE_MENU - 1))
                                                        map->mmain->choice = 0;
                                                else
                                                        map->mmain->choice++;
                                                break;
                                        case SDLK_UP: // Déplacer vers le haut
                                                if(map->mmain->choice == 0)
                                                        map->mmain->choice = NB_CHOICE_MENU - 1;
                                                else
                                                        map->mmain->choice--;
                                                break;
                                        case SDLK_RETURN:
                                                return map->mmain->choice;
                                                break;
                                        default :
                                                break;
                                }
                                SDL_BlitSurface(map->mmain->menu,NULL,map->wmain,&map->mmain->posm);
                                SDL_BlitSurface(map->mmain->menu_c[map->mmain->choice],NULL,map->wmain,&map->mmain->posm);
                                SDL_BlitSurface(map->mmain->menu_m,NULL,map->wmain,&map->mmain->posm);
                                SDL_Flip(map->wmain);
                                break;
                        default :
                                break;
                }
        }
        return 0;
}


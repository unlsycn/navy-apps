#include <NDL.h>
#include <stdio.h>

#include <sdl-timer.h>

#include "debug.h"

SDL_TimerID SDL_AddTimer(uint32_t interval, SDL_NewTimerCallback callback, void *param)
{
    panic("Not implement");
    return NULL;
}

int SDL_RemoveTimer(SDL_TimerID id)
{
    panic("Not implement");
    return 1;
}

uint32_t SDL_GetTicks()
{
    return NDL_GetTicks();
}

void SDL_Delay(uint32_t ms)
{
    uint32_t begin = SDL_GetTicks();
    uint32_t now;
    while ((now = SDL_GetTicks()) - begin < ms)
        ;
}

#include "debug.h"
#include <NDL.h>
#include <SDL.h>
#include <assert.h>
#include <string.h>

#define keyname(k) #k,
#define keystate(k) 0,

static const char *keyname[] = {"NONE", _KEYS(keyname)};
static uint8_t keystate[] = {0, _KEYS(keystate)};

SDL_KeyboardEvent SDL_ParseNDLEvent(const char *nevent)
{
    SDL_KeyboardEvent event;
    char ntype;
    char key[32];
    sscanf(nevent, "k%c %s", &ntype, key);

    assert(ntype == 'd' || ntype == 'u');
    event.type = ntype == 'd' ? SDL_KEYDOWN : SDL_KEYUP;

    event.keysym.sym = SDLK_NONE;
    for (int i = 0; i < (int)(sizeof(keyname) / sizeof(const char *)); i++)
    {
        if (strcmp(key, keyname[i]) == 0)
        {
            event.keysym.sym = i;
            keystate[i] = event.type == SDL_KEYDOWN ? 1 : 0;
        }
    }
    return event;
}

int SDL_PushEvent(SDL_Event *ev)
{
    return 0;
}

int SDL_PollEvent(SDL_Event *ev)
{
    const int len = 32;
    char nevent[len];
    int ret = NDL_PollEvent(nevent, len);
    if (ret)
        *ev = (SDL_Event)SDL_ParseNDLEvent(nevent);
    return ret;
}

int SDL_WaitEvent(SDL_Event *ev)
{
    while (SDL_PollEvent(ev) == 0)
        ;
    return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
    panic("Not implement");
    return 0;
}

uint8_t *SDL_GetKeyState(int *numkeys)
{
    return keystate;
}

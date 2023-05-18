#include <NDL.h>
#include <SDL.h>
#include <assert.h>
#include <string.h>

#define keyname(k) #k,

static const char *keyname[] = {"NONE", _KEYS(keyname)};

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
            event.keysym.sym = i;
    }
    return event;
}

int SDL_PushEvent(SDL_Event *ev)
{
    return 0;
}

int SDL_PollEvent(SDL_Event *ev) {
  return 0;
}

int SDL_WaitEvent(SDL_Event *event) {
  const int len = 32;
  char nevent[len];
  while (NDL_PollEvent(nevent, len) == 0)
        ;
  *event = (SDL_Event)SDL_ParseNDLEvent(nevent);
  return 1;
}

int SDL_PeepEvents(SDL_Event *ev, int numevents, int action, uint32_t mask) {
  return 0;
}

uint8_t* SDL_GetKeyState(int *numkeys) {
  return NULL;
}

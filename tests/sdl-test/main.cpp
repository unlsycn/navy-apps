#include <SDL.h>
#include <SDL_bdf.h>
#include <assert.h>
#include <stdio.h>

#define W 48
#define H 16

static const char *font_fname = "/share/fonts/Courier-7.bdf";
static BDF_Font *font = NULL;
static SDL_Surface *screen = NULL;

int main()
{
    SDL_Init(0);
    font = new BDF_Font(font_fname);

    int win_w = font->w * W;
    int win_h = font->h * H;
    screen = SDL_SetVideoMode(win_w, win_h, 32, SDL_HWSURFACE);
    SDL_FillRect(screen, NULL, 0xffffff);

    SDL_Surface *s = BDF_CreateSurface(font, 'a', 0x323232, 0xf0f0f0);
    SDL_Rect dstrect = {.x = 0, .y = 0};
    SDL_BlitSurface(s, NULL, screen, &dstrect);
    SDL_FreeSurface(s);

    SDL_UpdateRect(screen, 0, 0, 0, 0);

    printf("Test ends! Spinning...\n");
    while (1)
        ;
    return 0;
}

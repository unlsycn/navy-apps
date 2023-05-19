#include <SDL.h>
#include <stdint.h>
#include <stdio.h>

int main()
{
    SDL_Init(0);
    while (1)
    {
        SDL_Delay(500);
        printf("ms\n");
    }
    return 0;
}
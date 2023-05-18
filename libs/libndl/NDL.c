#include "sys/time.h"
#include "sys/unistd.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;
static int canvas_w = 0, canvas_h = 0;

uint32_t NDL_GetTicks()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 10 + now.tv_usec / 1000;
}

int NDL_PollEvent(char *buf, int len)
{
    int fd = open("/dev/events", 0, 0);
    int ret = read(fd, buf, len);
    close(fd);
    return ret ? 1 : 0;
}

void NDL_OpenCanvas(int *w, int *h)
{
    if (*w == 0 && *h == 0)
    {
        *w = screen_w;
        *h = screen_h;
    }
    canvas_w = *w;
    canvas_h = *h;
    if (getenv("NWM_APP"))
    {
        int fbctl = 4;
        fbdev = 5;
        screen_w = *w;
        screen_h = *h;
        char buf[64];
        int len = sprintf(buf, "%d %d", screen_w, screen_h);
        // let NWM resize the window and create the frame buffer
        write(fbctl, buf, len);
        while (1)
        {
            // 3 = evtdev
            int nread = read(3, buf, sizeof(buf) - 1);
            if (nread <= 0)
                continue;
            buf[nread] = '\0';
            if (strcmp(buf, "mmap ok") == 0)
                break;
        }
        close(fbctl);
    }
}

void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h)
{
    int canvas_offx = (screen_w - canvas_w) / 2;
    int canvas_offy = (screen_h - canvas_h) / 2;
    int rect_offx = canvas_offx + x;
    int rect_offy = canvas_offy + y;
#ifdef __ISA_NATIVE__
    for (int i = 0; i < h; i++)
    {
        lseek(fbdev, ((rect_offy + i) * screen_w + rect_offx) * sizeof(uint32_t), SEEK_SET);
        write(fbdev, pixels + i * w, w * sizeof(uint32_t));
    }
#else
    lseek(fbdev, (rect_offy * screen_w + rect_offx) * sizeof(uint32_t), SEEK_SET);
    size_t size = w; // size is {32'w, 32'h}
    size <<= 32;
    size += h;
    write(fbdev, pixels, size);
#endif
}

void NDL_OpenAudio(int freq, int channels, int samples)
{
}

void NDL_CloseAudio()
{
}

int NDL_PlayAudio(void *buf, int len)
{
    return 0;
}

int NDL_QueryAudio()
{
    return 0;
}

int NDL_Init(uint32_t flags)
{
    if (getenv("NWM_APP"))
    {
        evtdev = 3;
    }
    int fd = open("/proc/dispinfo", 0, 0);
    char info[64];
    read(fd, info, 64);
    close(fd);
    sscanf(info, "WIDTH %*[: ]%d\nHEIGHT %*[: ]%d", &screen_w, &screen_h);
    return 0;
}

void NDL_Quit()
{
    canvas_w = 0;
    canvas_h = 0;
}

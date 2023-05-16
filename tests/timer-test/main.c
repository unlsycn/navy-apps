#include <NDL.h>
#include <stdint.h>
#include <stdio.h>

int main()
{
    NDL_Init(0);
    uint32_t now, last;
    while (1)
        if (now = NDL_GetTicks(), now - last >= 500)
        {
            last = now;
            printf("ms = %u\n", now);
        }
    return 0;
}
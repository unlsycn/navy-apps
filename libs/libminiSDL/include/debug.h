#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <assert.h>
#include <stdio.h>

#undef panic
#define panic(format, ...)                                                                            \
    do                                                                                                \
    {                                                                                                 \
        printf("[%s,%d,%s] system panic: " format "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        assert(0);                                                                                    \
    } while (0)

#endif
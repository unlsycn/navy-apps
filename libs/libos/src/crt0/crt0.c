#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]);
extern char **environ;
void call_main(uintptr_t *args)
{
    // argc
    args = (uintptr_t *)((uint64_t *)args - 1);
    int argc = *(int *)args;
    // argv
    char *argv[argc + 1];
    for (int i = 0; i <= argc; i++)
        argv[i] = *(char **)(--args);

    // envp
    int envc = 0;
    while (*(args - envc))
        envc++;
    char *envp[envc + 1];
    // using malloc() here before implementing VME leads to the argv and envp in the heap being overwritten if the new program
    // is larger than the current.
    for (int i = 0; i <= envc; i++)
        envp[i] = *(char **)(--args);
    environ = envp;

    exit(main(argc, argv, envp));
    assert(0);
}

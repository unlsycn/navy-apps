#include <SDL.h>
#include <nterm.h>
#include <stdarg.h>
#include <unistd.h>

char handle_key(SDL_Event *ev);

static void sh_printf(const char *format, ...)
{
    static char buf[256] = {};
    va_list ap;
    va_start(ap, format);
    int len = vsnprintf(buf, 256, format, ap);
    va_end(ap);
    term->write(buf, len);
}

static void sh_banner()
{
    sh_printf("Built-in Shell in NTerm (NJU Terminal)\n\n");
}

static void sh_prompt()
{
    sh_printf("sh> ");
}

static void sh_handle_cmd(const char *cmd)
{
#define MAX_TK 128
    char *tokens[MAX_TK];

    int tk_cnt = 0;
    char *token = strtok((char *)cmd, " ");
    while (token != NULL)
    {
        tokens[tk_cnt++] = token;
        token = strtok(NULL, " ");
    }
    assert(tk_cnt < MAX_TK);
    tokens[tk_cnt - 1][strlen(tokens[tk_cnt - 1]) - 1] = '\0'; // remove the last \n
    tokens[tk_cnt] = NULL;

    char *envp[] = {NULL};
    execve(tokens[0], tokens, envp);
}

void builtin_sh_run()
{
    sh_banner();
    sh_prompt();

    while (1)
    {
        SDL_Event ev;
        if (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_KEYUP || ev.type == SDL_KEYDOWN)
            {
                const char *res = term->keypress(handle_key(&ev));
                if (res)
                {
                    sh_handle_cmd(res);
                    sh_prompt();
                }
            }
        }
        refresh_terminal();
    }
}

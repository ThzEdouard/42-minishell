#include "../../include/minishell.h"

int     verification_quote(line)
{
    int start;
    char    c;

    start = 0;
    while (*line)
    {
        if (start == 0 && (*line == '\'' || *line == '\"'))
        {
            c = *line;
            start++;
        }
        if (start == 1 && *line == c)
            start = 0;
        line++;
    }
    if (start == 1)
        return (/*metre en meme temp le code error c'est a dire si c'est une simple quote ou double*/FAIL);
    return (SUCCESS);
}

void    prompt(/*voir ce qu'il y a pas a passer*/)
{
    char    *line;

    line = readline("doudou > ");
    while (line != NULL)
    {
        //ici on envoie la ligne vair le parsing est l'execution du programme
        free(line);
        line = readline("doudou > ");
    }
}
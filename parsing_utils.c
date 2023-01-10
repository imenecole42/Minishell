#include "minishell.h"
#include "Libft/libft.h"

int is_quote(char c)
{
    if(c == 34 || c == 39)
        return(1);
    return(0);
}

int check_open_quotes(const char *line)
{
    int open_dquotes;
    int open_squotes;

    open_dquotes = 0;
    open_squotes = 0;
    while (*line)
    {
        if (*line == 34 && is_even(open_squotes))
            open_dquotes++;
        else if (*line == 39 && is_even(open_dquotes))
            open_squotes++;
        line++;
    }
    if (!is_even(open_dquotes) || !is_even(open_squotes))
        return(1);
    return(0);
}
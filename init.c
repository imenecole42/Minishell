#include "minishell.h"
#include "Libft/libft.h"

int     dup_env(t_data *data, char **env)
{
    int i;
    int size;

    i = -1;
    size = 0;
    while (env[++i] != NULL)
    {
        size++;
        printf(BOLD_PURPLE"env[%d] == %s\n"RESET, i, env[i]);
    }
    data->env = ft_calloc(size + 1, sizeof(char**));
    if (!data->env)
        return(0);
    i = -1;
    while (env[++i] != NULL)
    {
        data->env[i] = ft_strdup(env[i]);
        if (!data->env[i])
            return(0);
    }
    return(1);
}

int    init_struct(t_data *data, char **env)
{
    //int mode;

    //mode = isatty(STDIN_FILENO);
    //if (mode != TRUE)
        //(EXIT_FAILURE); // faire fonction pour quitter proprement
    ft_bzero(data, sizeof(t_data));
    if (dup_env(data, env) == FALSE)
    {
        printf("error : initialization of environment");
        return (0);
    }
    

}
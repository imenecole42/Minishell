
#include "minishell.h"
#include "Libft/libft.h"

void    test_parse(t_data *data)
{
    t_data  *tmp;
    t_cmd   *cmd;

    tmp = data;
    print_token(&tmp->token);
    if (init_cmd(&cmd) == TRUE)
    {
        while (tmp->token)
        {
            //printf("entree boucle = %d\n", cmd->is_pipe);
            if (tmp->token->type == PIPE && tmp->token->qstatus == DEFAULT)
            {
                if (cmd->is_pipe == TRUE)
                    printf("error '||'\n");
                else
                    cmd->is_pipe = TRUE;
                //printf("%d\n", cmd->is_pipe);
            }
            tmp->token = tmp->token->next;
        }
    }
}


// int main(int ac, char **av)
// {
//     (void)ac;
//     (void)av;
    // printf("Hi there\n");
    // printf("EOF = %d\n", EOF);*/

    //executing an ls command
    //char *av2[] = {"ls", "-la", NULL};
    //execvp(av2[0], av2);
    //printf("...and done\n");

    // (void)ac;
    // (void)av;
    // pid_t   childpid;
    // printf("before fork: %d\n", getpid());
    // //fork creates a child ans returns its process ID
    // childpid = fork();
    // printf("after fork: %d\n", getpid());
    // exit(0);
// }

#include "minishell.h"
#include "Libft/libft.h"

/*t_list  *head = ft_lstnew(NULL);
t_list  *minishell = head->next;*/

/*void    display_prompt(void)
{
    char *prompt;
    
    prompt = "minishell>";
    printf("%s", prompt);

}*/

void    sig_handler(int signum)
{

    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

char    *display_prompt(void)
{
    static char *prompt;

    prompt = NULL;
    if (prompt)
    {
        free(prompt);
        prompt = NULL;
    }
    prompt = readline("🐚> ");
    if(ft_strlen(prompt) > 0)
        add_history(prompt);
    return (prompt);
}

int check_input(t_data *data)
{
    char    *tmp;

    tmp = NULL;
    tmp = ft_strdup(data->line);
    if(ft_strlen(tmp) > MAXLINE)
    {
        printf(BOLD_YELLOW"command line is too long\n You want to break the parsing or what?\n"RESET);
        free(data->line);
        free(tmp);
        return(1);
    }
    return(0);
}

int main(int argc, char **argv, char **env)
{
    (void)  argv;
    t_data  data;
    int i = -1;

    if (argc == 1)
    {
        if(init_struct(&data, env) == FALSE)
            return(1);  //data exit status = 1
        while (1)
        {
            signal(SIGINT, sig_handler);
            data.line = display_prompt();
            if (check_input(&data) == TRUE)
                return (-1);
            data.cmds->cmd = ft_split(data.line, 32);
            while (data.cmds->cmd[++i] != NULL)
            {
                printf(BOLD_GREEN"cmd[%d] == %s\n"RESET, i, data.cmd[i]);
            }
            i = -1;
            while (env[++i] != NULL)
            {
                printf(BOLD_PURPLE"env[%d] == %s\n"RESET, i, env[i]);
            }
            i = -1;
            if (ft_quotes(data.line))
            {
                printf("number is even\n");
            }
            else 
                printf("number is odd\n");
            //display_env(env);
            //ft_basic_functions(line, argv);
            //read_command(command, parameters); // read input from terminal
        //if (fork() != 0) //parent
           // wait(NULL); // wait for child
        //else
           // execve (command, parameters, 0); // execute command
        //return (0);
        }
    }
    else
        printf("error, too much arguments\n");

    return(0);
}

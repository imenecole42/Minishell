/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:51:07 by hferjani          #+#    #+#             */
/*   Updated: 2023/01/11 16:33:10 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
//#include "Libft/get_next_line.h"
#include "Libft/libft.h"
#include "style.h"

#define MAXLINE 1024
#define MAXARGS 128 // maxargs in struct can't be variable

#define PATH_MAX 4096

#define TRUE 1
#define FALSE 0

enum builtin
{	PWD,
        ECHO,
        CD,
        EXPORT,
        UNSET,
        ENV,
        EXIT,
        CLEAR,
        CAT,
};

typedef struct s_env
{
        char *content;
        struct s_env *next;
} t_env;

typedef struct  s_token
{
        char    *input;
        int     type;
        int     status;
        struct s_token  *prev;
        struct s_token  *next;
} t_token;

typedef struct  s_fd
{
        int     in;
        int     out;
} t_fd;

typedef struct s_cmd
{
        char    **cmd;
        t_fd    fd;
        char    *heredoc;
        struct s_cmd    *next;
        
} t_cmd;


typedef struct s_data
{
        char    *line;
        char    **env;
        t_cmd    *cmds;
        t_token *token;
        int     exit_status;
        //int     len;
} t_data;

/*init.c*/

int     init_struct(t_data *data, char **env);

/*free.c*/

void    free_array(char **array);

/*parser.*/

int    valid_syntax(char *line);

int     check_open_quotes(const char *line);
void    sig_handler(int signum);
char    *display_prompt(void);
void    ft_basic_functions(char *line, char **argv);
//void	built_in_pwd(void);
//void	built_in_cd(char *path);
int     is_even(int num);
int	ft_quotes(char *s);
char    **tokenizer(char *cmd_arg);
void	display_env(char **env);
int     is_space(char c);


#endif

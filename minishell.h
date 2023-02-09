/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:51:07 by hferjani          #+#    #+#             */
/*   Updated: 2023/02/09 12:04:06 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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
#include <stdbool.h>
#include <fcntl.h>
//#include "Libft/get_next_line.h"
#include "Libft/libft.h"
#include "style.h"

#define MAXLINE 1024
#define MAXARGS 128 // maxargs in struct can't be variable

#define PATH_MAX 4096

#define TRUE 1
#define FALSE 0

typedef struct s_env
{
        char *content;
        struct s_env *next;
} t_env;

/*typedef struct  s_token
{
        char    *input;
        int     type;
        int     status;
        struct s_token  *prev;
        struct s_token  *next;
} t_token;
*/

enum    e_state
{
    DEFAULT,
    SQUOTE,
    DQUOTE,
};

enum    e_type
{
    WORD,
    WHITESPACE,
    NEW_LINE,
    PIPE,
    HEREDOC,
    ENV,
    REDIR_IN,
    REDIR_OUT,
    DREDIR_OUT,
    S_QUOTE,
    D_QUOTE,
    STD_IN,
    TRUNC,
    APPEND,
    LIMITER,
};

//TOKENS

typedef struct  s_token
{
    char  *value;
    int   len;
    enum e_type   type;
    enum e_state   qstatus;
    struct s_token  *prev;
    struct s_token  *next;
} t_token;

/*typedef struct  s_fd
{
        int     in;
        int     out;
} t_fd;*/

typedef struct s_parse
{
        char    *str;
	int	cmd;
	enum e_type     type;
}	t_parse;

typedef struct s_cmd
{
        char    **cmd;
        int     fd_in;
        int     fd_out;
        char    *heredoc_limit;
        struct s_cmd    *next;
        //struct s_cmd    *prev;
        
} t_cmd;

typedef struct s_data
{
        char    *line;
        char    **env;
        t_cmd   *cmds;
        t_token *token;
        int     exit_status;
        //int     len;
} t_data;

/*init.c*/

int     init_struct(t_data *data, char **env);
t_cmd   *init_command(void);

/*free.c*/

void    free_array(char **array);

/*parser.c*/

int    valid_syntax(char *line);
int     forbidden_series(char *s);
//int   forbidden_series(t_token *token);

/*lexer_utils.c*/

int     is_ascii(char *s);
t_token *create_token(char *value, int len, enum e_type type, enum e_state status);
void	ft_lstadd_back_token(t_token **lst, t_token *new);
void	push(t_token **head_ref, t_token *new);
void    print_liste(t_token * head);
void    test_parse(t_data *data);
int     is_special_char(char *line, int i);
void    if_redir(t_token *lexer);
t_token *read_input(char *line);
void    print_token(t_token **head);
int     is_sep(char *line);
void    parse_cmd_table(t_token *lexer, t_cmd **cmd_line);
int     ft_count_word(t_token  *lexer);


int     check_open_quotes(const char *line);
int     open_quotes(const char *line, int pos);
int     begin_sep_error(char *line);
int     end_sep_error(char *line);
char    *parse_quotes(t_token *lexer);
int     save_dquotes(t_token **lexer, char *line, enum e_state status);

void    sig_handler(int signum);
void    free_check_input(char *s1, char *s2);
char    *display_prompt(void);
void    ft_basic_functions(char *line, char **argv);
int     is_even(int num);
int	ft_quotes(char *s);
int     do_not_implement(char *s);
void	display_env(char **env);
int     is_space(char *line);

#endif

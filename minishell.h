/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:51:07 by hferjani          #+#    #+#             */
/*   Updated: 2023/03/15 16:46:25 by hferjani         ###   ########.fr       */
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

// #define HEREDOC_PREFIX  "/tmp/.tmp.minishell.heredoc"
#define HEREDOC_PREFIX  ".tmp.minishell.heredoc"

#define PATH_MAX 4096

#define TRUE 1
#define FALSE 0

#define SHE 10
#define DFL 11
#define IGN 12

extern int      g_exit_code;

typedef struct s_env
{
        char *content;
        struct s_env *next;
} t_env;

# define ERR_INFILE "Infile"
# define ERR_HERDOC "herdoc"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe Failed"
# define ERR_FORK "fork failed\n"

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
        char    *heredoc_limit;
        int     fd_in;
        int     fd_out;
        int     here_doc;
        int     argc;
        pid_t   pid;
        pid_t	pid_one;
        struct s_cmd    *next;
        //struct s_cmd    *prev;
        
} t_cmd;

typedef struct s_data
{
        char    *line;
        char    **env;
        int	**pfd;
        t_cmd   *cmds;
        int     nbr_cmd;
        int     nbr_pipe;
        t_token *token;
        int     exit_status;
        int     argc;
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
void    print_liste(t_token *head);
void    print_list(t_env *head);
void    test_parse(t_data *data);
int     is_special_char(char *line, int i);
void    if_redir(t_token *lexer);
t_token *read_input(char *line);
void    print_token(t_token **head);
int     is_sep(char *line);
t_cmd    *parse_cmd_table(t_data *data, t_token *lexer);
void    ft_lstadd_back_command(t_cmd **lst, t_cmd *new);
int     ft_count_word(t_token  *lexer);
void	redefine_status(t_token *lexer);
int     ft_count_list(t_cmd *cur);


int     check_open_quotes(const char *line);
int     check_open_quotes_expand(const char *line, int pos);
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
char	*ft_strcpy(char *dest, char *src);
int	ft_strcmp(char *s1, char *s2);
int	ft_strlen_mat(char **tab);
int     ft_isalnum_mini(int c);
void    print_simple(char *str);
void    replace(t_data *data);
int     replacer(char *line, int pos);
int     expand_finder(char *str);
//char	*ft_strjoin_char(char const *s1, char s2);
char    *env_finder(char *line, int start, int end);
int     count_nodes(t_cmd *cmd_table);
void    init_expand_variables(int i, int start, int end, int dollar);
char    *ft_strdup_char(char c);
void    print_liste_cmd(t_cmd **head);
void    set_signal(int sig_int, int sig_quit);
// static char     *make_heredoc_name(void);
// static int	handle_heredoc(t_data *data, t_cmd *command, char *delimiter);
void	handle_heredoc(t_data *data, t_cmd *command, char *delimiter);
int	heredoc(t_data *data, t_cmd *cmd_line, char *delimeter, const char *tmp, int *fd_out);




// typedef struct s_data
// {
//         char    **env;
//         char    **export;
//         int     argc;
// } t_data;

//bullting
void realloc_env (t_data *mini,char *str);
int  ft_env(t_data *mini);
void get_env(t_data *mini,char **argv);
int  print_export(t_data *mini);
int	ft_echo(char **argv, t_data *mini);
int  ft_check(char *argv);
char *ft_get_add_env(t_data *mini,char *str);
void ft_export(char **argv,t_data *mini);
void ft_free(char **str);
int  is_plus(char *str);
int  is_export(char *str);
char *strdup_plus(char *str);
char *ft_select(char *str);
char *ft_select1(char *str);
char *ft_select2(char *str);
void realloc_env_be(t_data *mini, char *str);
void realloc_unset(t_data *mini,char *str);
void ft_unset(t_data *mini,char **argv);
int	ft_pwd(t_data *mini);
int	get_var(char *var, char **env);
int	strjoint_env(char *var, char *path, t_data *mini);
char	*get_home(t_data *mini,char *var);
int	cd_new_path(char **cmd, int i, t_data *mini, char *newpath);
int	ft_cd(char **cmd, int argc, t_data *mini);
int	is_exit(char *str);
void	ft_many_arg(t_data *mini);
void	ft_exit(t_data *mini, char **cmd);
int	is_builtin(t_data *mini, char **argv);
int	builtin_env(char **argv);
void 	util_unset(t_data *mini,int i,int j,char **temp);
char *get_var_echo(char *str);
char *get_val_echo(char *str);
char *check_var(char *str,t_data *mini);
char *get_val_echo_space(char *str);
int ft_print_var_quote(char *str,t_data *mini);
int ft_print_var_sans_quote(char *str,t_data *mini);

//  execution
void	ft_close_fd(t_cmd *cmd_exec);
void	ft_close(t_data *data, t_cmd *cmd_exec);
void	close_fd(t_data *data, t_cmd *cmd_exec);
void    exec_cmd(t_cmd *exec_cmd, t_data *data);
void    open_file(t_data *data, t_cmd *cmd_exec, int i);
void    exec_one_cmd(t_cmd *cmd_exec, t_data *data);
void    exec_pipe(t_cmd *cmd_exec, t_data *data);
void	free_pfd(t_data *data);
int	ft_free_pipes(t_data *data, int n);
void	creat_pipes(t_data *data);
void	ft_dup(int src, int dest);
void free_exeve(t_data *data, t_cmd *cmd_exec);
void	child(t_cmd *cmd_exec,t_data *data, char **envp);
void	msg_error1(char *err);
int	msg(char *err);
int	ft_no_path(char  **env);
char	**ft_get_path(char  **env);
char	*get_cmd(char *cmd, char **envp);
void	msg_error(char *err);
#endif

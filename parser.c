/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:17:01 by hferjani          #+#    #+#             */
/*   Updated: 2023/02/08 17:57:03 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

t_cmd    *init_command(void)
{
    t_cmd   *cmd_line;
    
    cmd_line = malloc(sizeof(t_cmd));
    if (cmd_line)
    {
        cmd_line->next = NULL;
        cmd_line->cmd = NULL;
        cmd_line->heredoc_limit = NULL;
        cmd_line->fd_in = -1;
        cmd_line->fd_out = -1;
    }
    return (cmd_line);
}

/*void    handle_input(t_cmd  *cmd_line, char *filename)
{
    int fd_in;

    fd_in = open(filename, O_RDONLY);
    if (fd_in < 0)
    {
        perror(strerror(errno));
    }
    cmd_line->fd_in = fd_in;
}

void    handle_output_simple(t_cmd  *cmd_line, char *filename)
{
    int fd_out;
    
    fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd_out < 0)
    {
        perror(strerror(errno));
    }
    cmd_line->fd_out = fd_out;
}

void    handle_output_double(t_cmd  *cmd_line, char *filename)
{
    int fd_out;
    
    fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (fd_out < 0)
    {
        perror(strerror(errno));
    }
    cmd_line->fd_out = fd_out;
}

void    handle_heredoc(t_cmd *cmd_line, char *delimiter)
{
    int fd_in;
    char *filename;
    
    filename = NULL;
    
}
*/
void    parse_string(char *content,int len, char **argv, int i)
{
    int j;
    
    j = 0;
    //printf("i : %i\n", i);
    argv[i] = malloc(sizeof(char) * (len + 1));
    if (argv[i] == NULL)
        return ;
    while (j < len)
    {
        argv[i][j] = content[j];
        j++;
    }
    argv[i][j] = '\0';
    //printf("argv i j : %s\n", argv[i]);
    return ;
}

void    parse_cmd_table(t_token *lexer, t_cmd **cmd_line)
{
    t_token *cur;
    int i;
    int count_word;
    
    cur = lexer;
    i = 0;
    count_word = ft_count_word(cur);
    while (cur)
    {
        if (cur->type == PIPE)
        {
            (*cmd_line)->next = init_command();
            (*cmd_line) = (*cmd_line)->next;
            i = 0;
        }
        else
        {
            (*cmd_line)->cmd = malloc(sizeof(char *) * (count_word + 1));
            if((*cmd_line)->cmd == NULL)
                return ;
            if (cur->type == WORD)
            {
                parse_string(cur->value, cur->len, (*cmd_line)->cmd, i);
                printf("************************************************\n");
                printf("*argv[%i] :", i);
                printf("%s\n", (*cmd_line)->cmd[i]);
                printf("************************************************\n");
                i++;
            }
        }
        /*if (cur->type == OPEN_FILE)
            handle_input(*cmd_line, cur->value);
        if (cur->type == EXIT_FILE)
            handle_output_simple(*cmd_line, cur->value);
        if (cur->type == EXIT_FILE_RET)
            handle_output_double(*cmd_line, cur->value);
        if (cur->type == LIMITER)
            handle_heredoc(*cmd_line, cur->value);*/
        cur = cur->next;
        
    }

}

int ft_count_word(t_token  *lexer)
{
    t_token *tmp;
    int    count;

    tmp = lexer;
    count = 0;
    while (tmp && tmp->type != PIPE)
    {
        if (tmp->type == WORD)
        {
            count++;
        }
        tmp = tmp->next;
    }
    return (count);
}
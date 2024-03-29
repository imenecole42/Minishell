/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:17:01 by hferjani          #+#    #+#             */
/*   Updated: 2023/03/15 17:20:48 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

// t_cmd    *init_command(void)
// {
//     t_cmd   *cmd_line;
    
//     cmd_line = malloc(sizeof(t_cmd));
//     if (cmd_line)
//     {
//         cmd_line->next = NULL;
//         cmd_line->cmd = NULL;
//         cmd_line->heredoc_limit = NULL;
//         cmd_line->i = 0;
//         cmd_line->argc = 0;
//         cmd_line->here_doc = 0;
//         cmd_line->nbr_cmd = 0;
//         cmd_line->nbr_pipe = 0;
//         cmd_line->fd_in = -1;
//         cmd_line->fd_out = -1;
//     }
//     return (cmd_line);
// }

t_cmd   *create_cmd(int count_word)
{
    t_cmd   *cmd_line;

    cmd_line = malloc(sizeof(t_cmd));
    if(!cmd_line)
        return (NULL);
    cmd_line->cmd = malloc(sizeof(char *) * (count_word + 1));
    if(cmd_line->cmd == NULL)
        return (NULL);
    cmd_line->next = NULL;
    cmd_line->heredoc_limit = NULL;
    cmd_line->argc = 0;
    //cmd_line->nbr_pipe = 0;
    return(cmd_line);
    
}
void    handle_input(t_cmd  *cmd_line, char *filename)
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


char    *parse_string(char *content,int len, char **argv, int i)
{
    int j;
    
    j = 0;
    argv[i] = malloc(sizeof(char) * (len + 1));
    if (argv[i] == NULL)
        return (NULL);
    while (j < len && content[j] && argv)
    {
        
        argv[i][j] = content[j];
        j++;
    }
    argv[i][j] = '\0';
    return (argv[i]);
}

static char	*make_heredoc_name(void)
{
	static int	i;
	char		*name;
    //char *s1;
	char		*number;

    //s1 = ft_strdup(HEREDOC_PREFIX);
	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(ft_strdup(HEREDOC_PREFIX), number);
	free(number);
	i++;
	return (name);
}

void    handle_heredoc(t_data *data, t_cmd *cmd_line, char *delimiter)
{
    // (void)data;
    // (void)cmd_line;
    // (void)delimiter;
    int fd;
    int status;
    char *heredoc_name;
    
    heredoc_name = NULL;
    heredoc_name = make_heredoc_name();
	printf(BOLD_BLUE"%s\n"RESET, heredoc_name);
    status = heredoc(data, cmd_line,delimiter,heredoc_name, &fd);
    //printf("%d\n", status);
    if (status)
	{
		// unlink(heredoc_name);
		// free(heredoc_name);
		//return (status);
	}
    //return(status);
}

t_cmd    *parse_cmd_table(t_data *data, t_token *lexer)
{
    (void)data;
    t_token *cur;
    t_cmd   *ret;
    t_cmd   *ret_tmp;
    int i;
    int count_word;
    int pipe;
    //int node;
    
    cur = lexer;
    pipe = 0;
    i = 0;
    //node = 0;
    count_word = ft_count_word(cur);
    ret = create_cmd(count_word);
    ret_tmp = ret;
    while (cur)
    {
        if (cur->type == PIPE)
        {
            count_word = ft_count_word(cur->next);
            printf("pipe count word :%d\n", count_word);
            ft_lstadd_back_command(&ret, create_cmd(count_word));
            pipe++;
            i = 0;
            ret = ret->next;
            // ret->cmd = malloc(sizeof(char *) * (count_word + 1));
            // if(ret->cmd == NULL)
            //     return (NULL);
        }
        else if (cur->type == STD_IN)
            handle_input(ret, cur->value);
        else if (cur->type == TRUNC)
        {
            if(ret->fd_out > 0)
                close(ret->fd_out);
            handle_output_simple(ret, cur->value);
        }
        else if (cur->type == APPEND)
            {if (ret->fd_out > 0)
                close(ret->fd_out);
            handle_output_double(ret, cur->value);}
        else if (cur->type == LIMITER)
        {
            //printf("ok\n");
            handle_heredoc(data, ret, cur->value);
        }
        else
        {
            if (cur->type == WORD)
            {
                ret->cmd[i] = parse_string(cur->value, cur->len, ret->cmd, i);
                printf("************************************************\n");
                printf("*argv[%i] :", i);
                printf("%s\n", ret->cmd[i]);
                printf("************************************************\n");
                i++;
                ret->argc = i;
            }
        }
        cur = cur->next;
    }
    //node = ft_count_list(ret_tmp);
    //printf("nodes = %d\n", node);
    return(ret_tmp);
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

int ft_count_list(t_cmd *cur)
{
    t_cmd   *cmd_list;
    int count;

    cmd_list = cur;
    count = 0;
    while (cmd_list)
    {
        count++;
        cmd_list = cmd_list->next;
    }
    return(count);
}
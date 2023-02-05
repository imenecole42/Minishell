/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:17:01 by hferjani          #+#    #+#             */
/*   Updated: 2023/01/28 00:22:12 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

/*char *parse_quotes(t_token *lexer)
{
    char    *s = ft_strdup("");
    t_token *cur;
    cur = lexer;
    
    while (cur != NULL)
    {
        if (cur->type == S_QUOTE || cur->type == D_QUOTE)
        {
            cur = cur->next;
            while (cur->qstatus != DEFAULT)
            {
                s = ft_strjoin(s, cur->value);
                cur = cur->next;
                //break;
            }
        }
        cur = cur->next;
    }
    return (s);
}*/

void    parse(t_token *lexer, t_cmd *cmd)
{
    char    *str;
    t_token *cur;
    int     quotes;
    int     pipe;
    t_cmd   *next;

    str = NULL;
    cur = lexer;
    quotes = 0;
    pipe = 0;
    while (cur != NULL)
    {
        if (cur->type == PIPE)
        {
            if (pipe == 1)
                printf("error '||\n"); // creer fonction erreur
            cmd->is_pipe = true;
            cmd->cmd = 
        }
        
    }
    
}
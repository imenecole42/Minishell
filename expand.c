/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:46:37 by hferjani          #+#    #+#             */
/*   Updated: 2023/02/13 16:58:18 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    replace(char *str, char **env)
{ 
    (void)env;
    int i;
    //int len;
    int flag_quotes;

    i = 0;
    while (str[i])
    {
        flag_quotes = open_quotes(str, i);
        printf("%d\n",flag_quotes);
        i++;
    }
    
}
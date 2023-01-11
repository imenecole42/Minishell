/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:59:25 by hferjani          #+#    #+#             */
/*   Updated: 2023/01/11 15:19:49 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

/*static char *built_in_pwd(void)
{
    char    *cwd;
    int     len;
    
    len = PATH_MAX + ft_strlen("PWD=") + 1;
    cwd = ft_calloc(len, sizeof(char));
    if (!cwd)
        return (NULL);
    ft_strlcat(cwd, "PWD=", len);
    if (getcwd(&cwd[4], PATH_MAX == NULL))
    {
        perror("getcwd()");
    }
    return (cwd);
} */
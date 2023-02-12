/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_bullting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:31:19 by imraoui           #+#    #+#             */
/*   Updated: 2023/02/12 13:17:51 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

// int	is_builtin(t_data *mini, char **argv)
// {
// 	if (!argv[0])
// 		return (-1);
// 	g_status = 0;
// 	if (ft_strcmp(argv[0], "exit") == 0)
// 		return (ft_exit(mini, argv), g_status);
// 	else if (ft_strcmp(argv[0], "pwd") == 0 && go_in_builtin(argv[1]) == 1)
// 		return (ft_pwd(mini), g_status);
// 	else if (ft_strcmp(argv[0], "cd") == 0)
// 	{
// 		if (ft_cd(argv, 1, mini) == 1)
// 			g_status = 1;
// 		return (g_status);
// 	}
// 	else if (ft_strcmp(argv[0], "echo") == 0)
// 		return (ft_echo(argv, mini), g_status);
// 	else if (ft_strcmp(argv[0], "export") == 0)
// 		return (ft_export(argv, mini), g_status);
// 	if (ft_strcmp(argv[0], "unset") == 0)
// 		return (ft_unset(mini, argv), g_status);
// 	if (ft_strcmp(argv[0], "env") == 0 && !argv[1])
// 		return (ft_env(mini->env), g_status);
// 	return (-1);
// }

// int	builtin_env(char **argv)
// {
// 	if (!argv[0])
// 		return (-1);
// 	if (ft_strcmp(argv[0], "cd") == 0)
// 		return (1);
// 	if (ft_strcmp(argv[0], "export") == 0)
// 		return (1);
// 	if (ft_strcmp(argv[0], "unset") == 0)
// 		return (1);
// 	if (ft_strcmp(argv[0], "exit") == 0)
// 		return (1);
// 	return (0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:55:49 by imraoui           #+#    #+#             */
/*   Updated: 2023/02/03 15:13:04 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] == '-')
	{
		while (argv[i] == 'n')
			i++;
		if (argv[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_echo(char **argv, t_data *mini)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (i < mini->argc - 1)
		i++;
	while (argv[i][j] && i <= mini->argc - 1)
	{
		write(1, &argv[i][j], 1);
		j++;
	}
	i--;
	if (!ft_check(argv[i]))
		write(1, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:21:30 by imraoui           #+#    #+#             */
/*   Updated: 2023/03/14 08:11:31 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_env(t_data *mini, char *str)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	while (mini->env[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return ;
	temp[i + 1] = 0;
	while (mini->env[j])
	{
		temp[j] = mini->env[j];
		j++;
	}
	temp[i] = ft_get_add_env(mini, str);
	free (mini->env);
	mini->env = temp;
}

int	ft_env(t_data *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		printf("%s\n", mini->env[i]);
		i++;
	}
	return (0);
}

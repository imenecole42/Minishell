/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:39:38 by imraoui           #+#    #+#             */
/*   Updated: 2023/03/10 04:17:04 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export(t_data *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		printf("export -x ");
		printf("%s", ft_select(mini->env[i]));
		printf("\"%s\"\n", ft_select1(mini->env[i]));
		i++;
	}
	return (0);
}

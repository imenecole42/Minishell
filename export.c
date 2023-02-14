/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:13:44 by imraoui           #+#    #+#             */
/*   Updated: 2023/02/14 12:19:54 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_env_be(t_data *mini, char *str)
{
	char	*var;
	char	*val;
	char	*env;
	char	*temp;
	int		i;

	i = 0;
	var = ft_select(str);
	val = ft_select1(str);
	while (!ft_strnstr(mini->env[i], var, ft_strlen(var)))
		i++;
	env = mini->env[i];
	if (is_plus(str))
	{
		temp = ft_strjoin(env, val);
		mini->env[i] = temp;
	}
	else if (!is_plus(str))
	{
		free(mini->env[i]);
		temp = ft_strdup(str);
		mini->env[i] = temp;
	}
	return ;
}

char	*ft_get_add_env(t_data *mini, char *str)
{
	char	*var;
	char	*val;
	char	*temp;
	int		i;

	var = ft_select(str);
	val = ft_select1(str);
	i = 0;
	while ((mini->env[i]) && (!ft_strnstr(mini->env[i], var, ft_strlen(var))))
		i++;
	if (mini->env[i] == 0)
	{
		if (val && !is_plus(str))
		{
			temp = ft_strdup(str);
			mini->env[i] = temp;
		}
		else if (val && is_plus(str))
		{
			temp = strdup_plus(str);
			mini->env[i] = temp;
		}
	}
	return (mini->env[i]);
}

void	get_env(t_data *mini, char *dest)
{
	int	i;

	i = 0;
	while (mini->env[i] && (!ft_strnstr(mini->env[i], ft_select(dest),
				ft_strlen(ft_select(dest)))))
		i++;
	if (mini->env[i + 1] == 0)
		realloc_env(mini, dest);
	else
		realloc_env_be(mini, dest);
}

/*void	ft_export(char **argv, t_data *mini)
{
	if (mini->argc == 2)
		print_export(mini);
	if (mini->argc == 3)
	{
		if (is_export(argv[2]) && ft_select1(argv[2]))
		{
			get_env(mini, argv);
			get_export(mini, argv);
		}
		else if (is_export(argv[2]) && !ft_select1(argv[2]))
			get_export(mini, argv);
		else
		{
			write(2, "export: `", 10);
			ft_putstr_fd(argv[2], 2);
			write(2, "': not a valid identifier\n", 27);
		}
	}
	return ;
}*/

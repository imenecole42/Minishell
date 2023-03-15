/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:32:08 by imraoui           #+#    #+#             */
/*   Updated: 2023/03/15 17:53:09 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_exeve(t_data *data, t_cmd *cmd_exec)
{
	ft_free(cmd_exec->cmd);
	//free(pipex->pid);
	free_pfd(data);
	exit(127);
}

void	ft_dup(int src, int dest)
{
	dup2(src, 1);
	dup2(dest, 0);
}
void	child(t_cmd *cmd_exec,t_data *data, char **envp)
{
	
	if(cmd_exec->cmd[0] && builtin_env(cmd_exec->cmd) == 1)
	{
		is_builtin(data,cmd_exec->cmd);
	}
	if (cmd_exec->cmd[0] && !builtin_env(cmd_exec->cmd) && get_cmd(cmd_exec->cmd[0], envp))
	{
		execve(get_cmd(cmd_exec->cmd[0], envp), cmd_exec->cmd, envp);
		free_exeve(data,cmd_exec);
	}
	else
	{
		ft_putstr_fd(cmd_exec->cmd[0], 2);
		write(2, ": command not found\n", 20);
		free_exeve(data,cmd_exec);
	}		
}

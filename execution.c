/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:22:00 by imraoui           #+#    #+#             */
/*   Updated: 2023/03/14 10:33:11 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_cmd(t_cmd *exec_cmd, t_data *data)
{
	if (data->nbr_cmd == 1)
	{
		if (builtin_env(exec_cmd->cmd) == 1)
		{
			is_builtin(data, exec_cmd->cmd);
			return ;
		}
		else 
		{
			exec_one_cmd(exec_cmd, data);
			return ;
		}
	}
	else
		exec_pipe(exec_cmd, data);
}

void open_file(t_data *data, t_cmd *cmd_exec, int i)
{
	

		if(i == 0)
		{
			if (cmd_exec->fd_in != -1)
				dup2(cmd_exec->fd_in,0);
			else
			{
				cmd_exec->fd_in = 0;
				dup2(cmd_exec->fd_in,0);
			}
			if (cmd_exec->fd_out != -1)
				dup2(cmd_exec->fd_out,1);
			else
				dup2(data->pfd[i][1],1);
			//ft_close(exec);
		}
		else if(i == 1)
		{
			if (cmd_exec->fd_in != -1)
				dup2(cmd_exec->fd_in,0);
			else
				dup2(data->pfd[i - 1][0],0);
			if (cmd_exec->fd_out != -1)
				dup2(cmd_exec->fd_out,1);
			else
				dup2(data->pfd[i][1],1);
		}
		else if (i == 2)
		{
			if (cmd_exec->fd_in != -1)
				dup2(cmd_exec->fd_in,0);
			else
			{
				dup2(data->pfd[i - 1][0],0);
			}
			if (cmd_exec->fd_out != -1)
				dup2(cmd_exec->fd_out,1);
			else
			{
				cmd_exec->fd_out = 1;
				dup2(cmd_exec->fd_out,1);
			}
			//ft_close(exec);
		}
	
}
	
void exec_one_cmd(t_cmd *cmd_exec, t_data *data)
{
	cmd_exec->pid_one = fork();
	if (cmd_exec->pid_one == -1)
		return (write(2, "Error Fork\n", 12), free(NULL));
	else if (cmd_exec->pid_one == 0)
	{
		if (cmd_exec->fd_in > 2)
			dup2(cmd_exec->fd_in, 0);
		if (cmd_exec->fd_out > 2)
			dup2(cmd_exec->fd_out, 1);
		if (cmd_exec->cmd[0] && get_cmd(cmd_exec->cmd[0], data->env))
		{
			execve(get_cmd(cmd_exec->cmd[0], data->env), cmd_exec->cmd, data->env);
			ft_free(cmd_exec->cmd);
			exit(127);
		}
		else
		{
			ft_putstr_fd(cmd_exec->cmd[0], 2);
			write(2, ": command not found\n", 20);
			ft_free(cmd_exec->cmd);
			exit(127);
		}
	}
	else
	{
		waitpid(cmd_exec->pid_one, 0, 0);
		ft_close_fd(cmd_exec);
	}
}

void exec_pipe(t_cmd *cmd_exec, t_data *data)
{
	int i = 0;
	int j = 0;
	t_cmd *tmp = cmd_exec;
	creat_pipes(data); 
	while (cmd_exec != NULL)
	{
		cmd_exec->pid = fork();
		if (cmd_exec->pid == -1)
			return (write(2, "Error Fork\n", 12), free(NULL));
		if (cmd_exec->pid == 0)
		{
			open_file(data, cmd_exec, i);
			ft_close(data, tmp);
			child(cmd_exec,data, data->env);
		}
		i++;
		cmd_exec = cmd_exec->next;
	}
	ft_close(data, tmp);
	while(j < i)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
		j++;
	}
}


#include "minishell.h"

void	free_pfd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_cmd)
	{
		free(data -> pfd[i]);
		i++;
	}
	free(data -> pfd);
}

int	ft_free_pipes(t_data *data, int n)
{
	int	i;

	i = -1;
	if (data -> pfd)
	{
		while (data -> pfd[++i] && i < n)
			free_pfd(data);
		free_pfd(data);
	}
	return (0);
}

void	creat_pipes(t_data *data)
{
	int i;
	i = -1;
	data->pfd= (int **)malloc(sizeof(int *) * (data->nbr_cmd + 1));
	if (!data->pfd)
		msg_error(ERR_PIPE);
	data->pfd[data->nbr_cmd] = 0;
	while (++i < data->nbr_cmd)
	{
		data->pfd[i] = (int *)malloc(sizeof(int) * (2));
		if ((!data->pfd[i]) || pipe(data->pfd[i]))
		{
			ft_free_pipes(data, i);
			msg_error(ERR_PIPE);
		}
	}
}
#include "minishell.h"
#include "Libft/libft.h"

int	fill_heredoc_file(t_data *data, char *delimeter, int fd)
{
	(void)data;
	//(void)fd;
	char	*string;
	//char	*expanded_str;
	int		flag_delimeter;

	string = NULL;
	//expanded_str = NULL;
	flag_delimeter = 0;
	string = readline(">");
	printf(RED"%d\n"RESET,ft_strcmp(delimeter, string));
	if (!string)
		return (printf("warning: here-document delimited by %s\n", delimeter),
			1);
	if (ft_strcmp(delimeter, string) != 0)
	{
	// 	expanded_str = pre_expand(mini, string);
	// 	if (expanded_str)
		ft_putendl_fd(string, fd);
	}
	else
		flag_delimeter = 1;
	if (string)
		free(string);
	// if (expanded_str)
	// 	free(expanded_str);
	return (flag_delimeter);
}

int	heredoc(t_data *data, t_cmd *cmd_line, char *delimeter, const char *tmp, int *fd_out)
{
	(void)fd_out;
	(void)cmd_line;
	int	done;
	int	fd;

	// g_sig.exit_step = 0;
	// g_sig.status = 0;
	fd = open(tmp, O_CREAT | O_RDWR | O_TRUNC, 0777);
	done = 0;
	//signal(SIGINT, sig_init);
	while (done == FALSE) //while (g_exit_code == 0 && !done)
	{
		done = fill_heredoc_file(data, delimeter, fd);
	}
	// if (g_exit_code != 0)
	// {
	// 	close(fd_in);
	// 	fd_in = -1;
	// }
	close(fd);
	//*fd_out = open(tmp, O_RDONLY);
	return (done); //(g_exit_code)
}

// void	change_input(t_cmd *command, int fd, char *heredoc_file)
// {
// 	if (command->fd_in > 0)
// 		close(command->fd_in);
// 	if (command->heredoc_file)
// 		unlink(command->heredoc_file);
// 	command->fd_in = fd;
// 	command->heredoc_file = heredoc_file;
// }
    

// void	handle_heredoc(t_data *data, t_cmd *command, char *delimiter)
// {
// 	int		fd;
// 	char	*filename;
// 	int		status;

// 	filename = NULL;
// 	filename = make_heredoc_name("/tmp/.tmp.minishell.heredoc");
// 	status = heredoc(data, delimiter, filename, &fd);
// 	if (status)
// 	{
// 		unlink(filename);
// 		free(filename);
// 		return (status);
// 	}
// 	//change_input(command, fd_in, filename);
// 	return (status);
// }

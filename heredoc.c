#include "minishell.h"

int	fill_heredoc_file(t_mini *mini, char *delimeter, int fd_in)
{
	char	*string;
	char	*expanded_str;
	int		done;

	string = NULL;
	expanded_str = NULL;
	done = 0;
	string = readline(">>>>>");
	if (!string)
		return (printf("warning: here-document delimited by %s\n", delimeter),
			1);
	if (!ft_strcmp(delimeter, string))
	{
		expanded_str = pre_expand(mini, string);
		if (expanded_str)
			ft_putendl_fd(string, fd_in);
	}
	else
		done = 1;
	if (string)
		free(string);
	if (expanded_str)
		free(expanded_str);
	return (done);
}

int	heredoc(t_mini *mini, char *delimeter, const char *in_file, int *fd_out)
{
	int	done;
	int	fd_in;

	// g_sig.exit_step = 0;
	// g_sig.status = 0;
	fd_in = open(in_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	done = 0;
	signal(SIGINT, sig_init);
	while (g_exit_code == 0 && !done)
	{
		done = fill_heredoc_file(mini, delimeter, fd_in);
	}
	if (g_exit_code != 0)
	{
		close(fd_in);
		fd_in = -1;
	}
	close(fd_in);
	*fd_out = open(in_file, O_RDONLY);
	return (g_exit_code);
}

char	*make_file_name(const char *filename_prefix)
{
	struct stat	st;
	char		*filename;
	char		*filename_suffix;
	int			found;
	int			index;

	found = 0;
	index = 0;
	while (!found && index < INT_MAX)
	{
		filename_suffix = ft_itoa(index);
		filename = ft_strjoin(filename_prefix, filename_suffix);
		if (filename_suffix == NULL || filename == NULL)
			return (NULL);
		if (stat(filename, &st) != 0)
			found = 1;
		free(filename_suffix);
		if (!found)
			free(filename);
		index += 1;
	}
	return (filename);
}

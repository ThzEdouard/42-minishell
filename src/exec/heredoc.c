/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 01:29:02 by aradice           #+#    #+#             */
/*   Updated: 2022/10/13 16:45:49 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void sig_int_here(int sig, siginfo_t *info, void *tmp)
{
	(void)sig;
	ft_putstr_fd("\b\b\n", 0);
	close(0);
	g_statesssss = 1300;
}
void	ft_heredoc(t_exec *data, int i, int *filenumber)
{
	char	*line;
	char	*tmpfilename;
	struct sigaction	sa;
	int savein;

	savein = dup(STDIN_FILENO);
	sa.sa_sigaction = sig_int_here;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	write(STDIN_FILENO, "> ", 2);
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		line = readline(STDIN_FILENO);
		if (!line || !ft_strncmp(line, data->filename[i],
				ft_strlen(data->filename[i])))
		{
			if (!line || ft_strlen(data->filename[i]) == (ft_strlen(line) - 1))
			{
				tmpfilename = ft_free2_strjoin("tmp", ft_itoa(*filenumber));
				if (g_statesssss == 1300)
				{
					dup2(savein, 0);
					close(savein);
				}else
				{
					ft_heredoc_3(data, line, tmpfilename, i);
				}
				init_sig();
				break ;
			}
		}
		ft_heredoc_2(line, data->file[i]);
	}
	free(data->filename[i]);
	data->filename[i] = tmpfilename;
}

void	ft_heredoc_2(char *line, int temp)
{
	write(temp, line, ft_strlen(line));
	free(line);
	write(STDIN_FILENO, "> ", 2);
}

void	ft_heredoc_3(t_exec *data, char *line, char *tmpfilename, int i)
{
	close(data->file[i]);
	if (line)
		free(line);
	data->file[i] = open(tmpfilename, O_RDONLY);
	if (data->file[i] == -1)
		ft_error("File Error");
}

int	ft_check_heredoc(t_exec *data)
{
	t_exec	*tmp;
	int		i;

	i = 0;
	tmp = data;
	while (tmp && tmp->type)
	{
		i = 0;
		while (tmp->type[i])
		{
			if (tmp->type[i] == HEREDOC)
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_unlink_heredoc(t_exec *tmp)
{
	int	i;

	if (ft_check_heredoc(tmp))
	{
		while (tmp)
		{
			i = 0;
			while (tmp->type[i] == HEREDOC)
			{
				if (unlink(tmp->filename[i]) == -1)
					ft_error("Temp File Error");
				i++;
			}
			tmp = tmp->next;
		}
	}
}

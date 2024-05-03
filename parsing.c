/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:41:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/05/03 15:17:28 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(int ac, char **av, t_p *p, char **envp)
{
	int		i;

	i = 0;
	if (ac < 5)
		parse_error(p);
	p->heredoc = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		ft_init_here_doc(p, av[2], av[ac - 1]);
	else
	{
		p->infile = open(av[1], O_RDONLY);
		if (p->infile < 0)
			parse_error(p);
		p->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (p->outfile < 0)
			end_pipex(p, 1, "Could't open the outfile");
	}
	p->envp = envp;
}

int	find_path(t_p *p, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			p->paths = ft_split(envp[i] + 5, ':');
			return (0);
		}
		i++;
	}
	return (1);
}

void	get_commands(int size, t_p *p, char **commands)
{
	int	i;

	p->commands = ft_calloc(sizeof(char *), (size - 3 + 1));
	p->full_command = ft_calloc(sizeof(char *), (size - 3 + 1));
	size--;
	i = 0;
	while ((i + 2 + p->heredoc) < size)
	{
		p->commands[i] = ft_split(commands[i + 2 + p->heredoc], ' ');
		if (!p->commands[i])
			end_pipex(p, 2, "Memory allocation failled");
		p->full_command[i] = command_check(p, p->commands[i][0]);
		i++;
	}
}

char	*command_check(t_p *p, char *command)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	while (p->paths[i])
	{
		tmp = ft_strjoin(p->paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	write (2, "Command not found\n", 18);
	end_pipex(p, 4, "Error\n");
	exit(EXIT_FAILURE);
}

void	sleeping(t_p *p)
{
	int	i;
	int	max_sleep;
	int	max_sleep_index;
	int	sleep_time;

	i = 0;
	max_sleep = INT_MIN;
	max_sleep_index = -1;
	while (p->commands[i])
	{
		if (ft_strncmp(p->commands[i][0], "sleep", 5) == 0)
		{
			sleep_time = ft_atoi(p->commands[i][1]);
			if (sleep_time > max_sleep)
			{
				max_sleep = sleep_time;
				max_sleep_index = i;
			}
		}
		i++;
	}
	if (max_sleep_index != -1)
		execve(p->full_command[max_sleep_index], \
		p->commands[max_sleep_index], p->envp);
}

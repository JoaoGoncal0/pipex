/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:02:49 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/30 18:18:08 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_redirect(t_p *p, int *out_pipe, int index)
{
	if (p->full_command[index + 1])
	{
		dup2(out_pipe[1], STDOUT_FILENO);
		// close(out_pipe[0]);
	}
	else
		dup2(p->outfile, STDOUT_FILENO);
	execve(p->full_command[index], p->commands[index], p->envp);
	perror("execve");
	exit(EXIT_FAILURE);
	
}


void	child_work(t_p *p)
{
	int	i;
	int	tmp_infile;

	tmp_infile = p->infile;
	i = 0;
	while (p->full_command[i])
	{
		dup2(tmp_infile, STDIN_FILENO);
		pipe(p->pipe);
		p->id = fork();
		if (p->id < 0 || p->pipe[0] < 0)
			end_pipex(p, 7, "Failed to Pipe/Fork");
		if (!p->id)
			child_redirect(p, p->pipe, i);
		else
		{
			close(p->pipe[1]);
			close(tmp_infile);
			tmp_infile = p->pipe[0];
			wait(0);
		}
		i++;
	}
	close(p->pipe[0]);
	close(p->outfile);
}

void	print_commands(t_p *p)
{
	int i = 0;
	int j;

	while (p->commands[i])
	{
		j = 0;
		while (p->commands[i][j])
		{
			printf("Command %d, Argument %d: %s\n", i, j, p->commands[i][j]);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_p	*p;
	int i;
	int max_sleep;
	int max_sleep_index = -1;
	
	i = 0;
	p = malloc(sizeof(t_p));
	init_pipex(ac, av, p, envp);
	if (find_path(p, envp) != 0)
		end_pipex(p, 5, "Failed to find Path");
	get_commands(ac, p, av);
	while (p->commands[i])
	{
		if (ft_strncmp(p->commands[i][0], "sleep", 6) == 0)
		{
			int sleep_time = atoi(p->commands[i][1]);
			if (sleep_time > max_sleep)
			{
				max_sleep = sleep_time;
				max_sleep_index = i;
			}
		}
		i++;
	}
	if (max_sleep_index != -1)
	{
		execve(p->full_command[max_sleep_index], p->commands[max_sleep_index], p->envp);
		printf("Maior tempo de espera: %d\n", max_sleep);
	}
	print_commands(p);
	child_work(p);
	end_pipex(p, 0, "");
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:02:49 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/26 15:36:22 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	child_redirect(t_p *p, int index)
{
	if (p->id == 0)
	{
		dup2 (p->infile, STDIN_FILENO);
		dup2 (p->pipe[1], STDOUT_FILENO);
	}
	else if (p->id == p->cmd_nbr - 1)
	{
		dup2 (p->pipe[1], STDIN_FILENO);
		dup2 (p->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2 (p->pipe[0], STDIN_FILENO);
		dup2 (p->pipe[1], STDOUT_FILENO);
	}
	execve(p->full_command[index], p->commands[index], p->envp);
	end_pipex(p, 1, "");
}

void	child_work(t_p *p)
{
	int	i;
	
	i = 0;
	while (p->full_command[i])
	{
		if (pipe(p->pipe) == -1)
			end_pipex(p, 1, "Error\n");
		p->pid = fork();
		if (p->pid < 0)
			end_pipex(p, 1, "Error\n");
		if (!p->pid)
			child_redirect(p, i);
		else
		{
			close(p->infile);
			close(p->pipe[1]);
			wait(0);
		}
		i++;
	}
	close(p->pipe[0]);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_p *p;
// 	int	i;

// 	i = 0;
// 	p = malloc(sizeof(t_p));

// 	find_path(p, envp);
// 	get_commands(ac, p, av);
// 	// while (p->paths[i])
// 	// {
// 	// 	printf("ENVP path = %s\n", p->paths[i]);
// 	// 	i++;
// 	// }
// 	while (p->full_command[i])
// 	{
// 		printf("Full command = %s\n", p->full_command[i]);
// 		i++;
// 	}
// 	return (0);
// }


int	main(int ac, char **av, char **envp)
{
	t_p	*p;

	p = malloc(sizeof(t_p));
	init_pipex(ac, av, p, envp);
	if (find_path(p, envp) != 0)
		end_pipex(p, 5, "Failed to find Path");
	printf("test1\n");
	get_commands(ac, p, av);
	child_work(p);
	end_pipex(p, 0, "");
	return (0);
}

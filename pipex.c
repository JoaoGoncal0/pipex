/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:02:49 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/18 14:51:13 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_work(t_p *p, int i, char **envp)
{
	if (pipe(p->pipe) == -1)
		err(p, "Error");
	p->pid = fork();
	if (p->pid < 0)
		err(p, "Error");
	if (p->pid == 0)
	{
		close (p->pipe[0]);
		if (p->id == 0)
		{
			dup2 (p->infile, STDIN_FILENO);
			dup2 (p->pipe[1], STDOUT_FILENO);
		}
		else if (p->id == p->cmd_nbr - 1)
		{
			dup2 (p->p[1], STDIN_FILENO);
			dup2 (p->outfile, STDOUT_FILENO);
		}
		else
		{
			dup2 (p->pipe[0], STDIN_FILENO);
			dup2 (p->pipe[1], STDOUT_FILENO);		
		}
		get_cmd(p, i);
		execve(p->cmd_path, p->cmd, envp);
	}
	close (p->pipe[1]);
	wait(NULL);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		printf("erro\n");
		return (EXIT_FAILURE);
	}
	
	int end[2];
	pid_t pid;
	char *infile = av[1];
	char *cmd1 = av[2];
	char *cmd2 = av[3];
	char *outfile = av[4];
	int f1;
	int f2;

	if (pipe(end) < 0)
	{
		printf("erro\n");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		printf("error\n");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	// Child process
	{
		f1 = open(infile, O_RDONLY);
		if (f1 < 0)
		{
			printf("erro\n");
			return (EXIT_FAILURE);
		}
		child_process(f1, end);
	}
	else
	// Parent process
	{
		f2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (f2 < 0)
		{
			printf("erro\n");
			return (EXIT_FAILURE);
		}
		parent_process(f2, end);
	}
	wait(NULL);
	return (EXIT_SUCCESS);
}

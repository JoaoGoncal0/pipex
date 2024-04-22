/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:02:49 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/22 18:06:06 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(t_p *p)
{
	int	i;
	
	i = 0;
	while (p->path[i])
		free(p->path[i++]);
	free(p->path);
	i = 0;
	while (p->args[i])
		free(p->args[i++]);
	free(p->args);
}

void	err(t_p *p, char *str)
{
	perror(str);
	free_all(p);
	exit(EXIT_FAILURE);
}

void	child_redirect(t_p *p)
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
}

void	child_work(t_p *p, char **envp)
{
	if (pipe(p->pipe) == -1)
		err(p, "Error\n");
	p->pid = fork();
	if (p->pid < 0)
		err(p, "Error\n");
	if (!p->pid)
	{
		if (p->id == 0)
			child_redirect(p);
		get_cmd(p, p->args[1]);
		execve(p->cmd_path, p->cmd, envp);
		perror("execve");
		free_all(p);
		exit(EXIT_FAILURE);
	}
	close (p->pipe[1]);
	wait(NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_p *p;

	if (ac < 5)
	{
		ft_putstr_fd("Not enough augments\n", 2);
		exit(EXIT_FAILURE);
	}
	p = malloc(sizeof(t_p));
	parsing(p, ac, av);
	p->cmd_nbr = ac - 3 - p->here_doc;
	find_cmd_path(p, envp);
	p->id = -1;
	while (++p->id < p->cmd_nbr)
		child_work(p, envp);
	if (p->here_doc)
		unlink("heredoc_tmp");
	free_all(p);
}


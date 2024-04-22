/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:46:40 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/22 14:25:58 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(char **av, int file)
{
	char	*buffer;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(av[2]);
	tmp2 = ft_strjoin(tmp, "\n");
	while (1)
	{
		write (1,"pipe heredoc> ", 14);
		buffer = get_next_line(0);
		if (buffer)
		{
			if (ft_strlen(buffer) == ft_strlen(tmp2))
				if (!ft_strncmp(buffer, tmp2, ft_strlen(av[2])))
					break;
			write (file, buffer, ft_strlen(buffer));
			free(buffer);
		}
	}
	free(tmp);
	free(tmp2);
	free(buffer);
}

void	append(t_p *p, int ac, char **av)
{
	int	file;

	if (ac < 6)
	{
		ft_putstr_fd("Not enough augments\n", 2);
		exit(EXIT_FAILURE);
	}
	p->here_doc = 1;
	file = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	p->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file < 0 || p->outfile < 0)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
}

void	redirect(t_p *p, int ac, char **av)
{
	p->here_doc = 0;
	p->infile = open(av[1], O_RDONLY, 0644);
	if (p->infile < 0)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	p->outfile = open(av[ac - 1], O_RDONLY | O_CREAT | O_TRUNC, 0644);
	if (p->outfile < 0)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
}

void	parsing(t_p *p, int ac, char **av)
{
	int	i;
	int	j;

	if (!ft_strncmp(av[1], "here_doc", 9))
		append(p, ac, av);
	else
		redirect(p , ac, av);
	i = 1;
	j = -1;
	while (++i < ac)
		p->args[++j] = ft_strdup(av[i]);
	p->args[++j] = 0;
}
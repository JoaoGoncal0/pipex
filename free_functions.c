/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:55:23 by jomendes          #+#    #+#             */
/*   Updated: 2024/05/01 12:35:06 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	parse_error(t_p *p)
{
	write (2, "Error\n", 6);
	free(p);
	exit(EXIT_FAILURE);
}

void	free_array(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	free_commands(char ***commands)
{
	int	i;
	int	j;

	i = 0;
	if (commands)
	{
		i = 0;
		while (commands[i])
		{
			j = 0;
			while (commands[i][j])
				free(commands[i][j++]);
			free(commands[i++]);
		}
	}
	free(commands);
}

void	end_pipex(t_p *p, int exit_status, char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	free_array(p->paths);
	free_array(p->full_command);
	free_commands(p->commands);
	close(p->infile);
	close(p->outfile);
	free(p);
	exit(exit_status);
}
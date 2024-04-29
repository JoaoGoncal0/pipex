/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:46:40 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/29 18:19:34 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_here_doc(char *str, char *LIMITER, int line)
{
	char	**input_here_doc;

	input_here_doc = NULL;
	if (ft_strncmp(str, LIMITER, ft_strlen(LIMITER)) == 0 && (str[ft_strlen(LIMITER)] == '\n'))
	{
		input_here_doc = ft_calloc(sizeof(char *), (line + 2));
		free(str);
	}
	else
	{
		ft_printf("pipe heredoc> ");
		input_here_doc = ft_here_doc(get_next_line(0), LIMITER, (line + 1));
		input_here_doc[line] = str;
	}
	return (input_here_doc);
}

void	ft_init_here_doc(t_p *p, char *LIMITER, char *outfile)
{
	char	**input;
	int	i;

	ft_printf("pipe heredoc> ");
	input = ft_here_doc(get_next_line(0), LIMITER, 0);
	pipe(p->pipe);
	i = 0;
	while (input[i])
	{
		write (p->pipe[1], input[i], ft_strlen(input[i]));
		free(input[i]);
		i++;
	}
	close(p->pipe[1]);
	free(input);
	p->infile = p->pipe[0];
	p->outfile = open(outfile, O_CREAT | O_WRONLY, 0644);
	if (p->outfile < 0)
		end_pipex(p, 1, "Coudln't open Outfile");
}
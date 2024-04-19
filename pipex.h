/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:02:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/18 15:24:43 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_p
{
	int				 infile;
	int				outile;
	int				pipe[2];
	int				id;
	pid_t			pid;
	int				cmd_nbr;
	char			**cmd;
	char			**path;
	char			**cmd_path;
	char			*cmd;
	char			*env;
	int				here_doc;
}		t_p;

#endif
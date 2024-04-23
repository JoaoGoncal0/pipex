/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:02:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/23 14:30:47 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include "libft/libft.h"
# include "get_next_line/get_next_line_bonus.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_p
{
	int				 infile;
	int				outfile;
	int				pipe[2];
	int				id;
	pid_t			pid;
	int				cmd_nbr;
	char			**path;
	char			*cmd_path;
	char			**cmd;
	char			*env;
	int				here_doc;
	char			**args;
}		t_p;

void			free_paths(char **str);
void			find_path(t_p *p, char **envp);
void			find_cmd_path(t_p *p, char **av, char **envp);
void			get_cmd(t_p *p, char *tmp);
int				check_file_permission(const char *file);
int				check_command(char *command);
void			here_doc(char **av, int file);
void			append(t_p *p, int ac, char **av);
void			redirect(t_p *p, int ac, char **av);
void			parsing(t_p *p, int ac, char **av);
void			child_work(t_p *p, char **envp);
void			child_redirect(t_p *p);
void			free_all(t_p *p);
void			err(t_p *p, char *str);
int				main(int ac, char **av, char **envp);


#endif
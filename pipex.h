/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:02:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/05/02 17:23:00 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "get_next_line/get_next_line_bonus.h"
# include "ft_printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <limits.h>

typedef struct s_p
{
	int				infile;
	int				outfile;
	int				pipe[2];
	int				id;
	int				heredoc;
	pid_t			pid;
	char			**envp;
	char			**paths;
	char			**full_command;
	char			***commands;
}		t_p;

int				main(int ac, char **av, char **envp);
int				find_path(t_p *p, char **envp);
char			*command_check(t_p *p, char *command);
void			free_commands(char ***commands);
void			free_array(char **str);
void			end_pipex(t_p *p, int exit_status, char *str);
void			init_pipex(int ac, char **av, t_p *p, char **envp);
void			get_commands(int size, t_p *p, char **commands);
char			**ft_here_doc(char *str, char *LIMITER, int line);
void			ft_init_here_doc(t_p *p, char *LIMITER, char *outfile);
void			child_work(t_p *p);
void			child_redirect(t_p *p, int *out_pipe, int index);
// void			print_commands(t_p *p);
void			parse_error(t_p *p);
void			sleeping(t_p *p);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:41:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/26 15:36:54 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(int ac, char **av, t_p *p, char **envp)
{
	if (ac < 5)
		end_pipex(p, 1, "Wrong augments\n");
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
		ft_init_here_doc(p, av[2], av[ac - 1]);
	else
	{
		p->infile = open(av[1], O_RDONLY);
		if (p->infile < 0)
			write (2, "No such file or directory\n", 26);
		p->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (p->outfile < 0)
			end_pipex(p, 1, "Could't open the outfile");
	}
	p->envp = envp;
}

int	find_path(t_p *p, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if(ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			p->paths = ft_split(envp[i] + 5, ':');
			return (0);
		}
		printf("o path = %s", p->paths[i]);
		i++;
	}
	return (1);
}

void	get_commands(int size, t_p *p, char **commands)
{
	int	i;

	p->commands = ft_calloc(sizeof(char *), (size - 3 + 1));
	p->full_command = ft_calloc(sizeof(char *), (size - 3 + 1));
	size--;
	i = 0;
	while ((i + 2) < size)
	{
		p->commands[i] = ft_split(commands[i + 2], ' ');
		if (!p->commands[i])
			end_pipex(p, 2, "Memory allocation failled");
		p->full_command[i] = command_check(p, p->commands[i][0]);
		i++;
	}
}

char *command_check(t_p *p, char *command)
{
    int i = 0;
    char *full_path;

    if (!access(command, F_OK | X_OK))
        return ft_strdup(command);
    while (p->paths[i])
    {
        full_path = ft_strjoin(p->paths[i], "/");
        full_path = ft_strjoin(full_path, command);
        if (!access(full_path, F_OK | X_OK))
            return full_path;
        free(full_path);
        i++;
    }
 	write (2, "Command not found\n", 18);
    exit(EXIT_FAILURE);
}

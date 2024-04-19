/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:41:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/04/18 17:03:03 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **str)
{
	int	i;
	
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

// Saber onde o Path esta no envp

void	find_path(t_p *p, char **envp)
{
	int	i;
	char *tmp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=/home", 10) == 0)
			tmp = ft_strdup(envp[i] + 5);
		i++;
	}
	if (!tmp)
		printf("Erro\n");
	p->path = ft_split(tmp, ":");
	free(tmp);
}

// Procurar o path para o comando no envp

int	find_cmd_path(t_p *p, char **envp)
{
	char *tmp;
	char *tmp2;
	int fd;
	int i;

	find_path(p, envp);
	i = 0;
	while (p->path[i])
	{
		tmp = ft_strjoin(p->path[i], "/");
		tmp2 = ft_strjoin(tmp, p->cmd);
		fd = open(tmp2, O_RDONLY);
		if (fd >= 0)
		{
			p->cmd_path = ft_strdup(tmp2);
			free(tmp);
			free(tmp2);
			return (0);
		}
		i++;
		free(tmp);
		free(tmp2);
	}
	return (1);
}

// "ls -l" devolve so o "ls"

void	get_cmd(t_p *p, char *tmp)
{
	int i;
	char *cmd;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == ' ')
			break;
		i++;
	}
	cmd = ft_substr(tmp, 0, i);
	p->cmd = ft_split(cmd, " ");
	free(cmd);
}

int	check_file_permission(const char *file)
{
	if (file == NULL || *file == '\0')
		return (1);
	if (access(file, F_OK) == 0)
		return (0);
	if (access(file, X_OK) == 0)
		return (0);
	else
		perror("Error\n");
}

int	check_command(char *command)
{
	int	i;

	i = 0;
	if (!command)
		return (1);
	while (command[i])
	{
		if (!(command[i] >= 'a' && command[i] <= 'z'))
		{
			printf("Command doesnt exist\n");
			return (1);
		}
		i++;
	}
	return (0);
}
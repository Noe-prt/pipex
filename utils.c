/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:56:34 by nopareti          #+#    #+#             */
/*   Updated: 2024/12/01 18:01:15 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_splitted_path(char **envp)
{
	int		i;
	char	**splitted_path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	splitted_path = ft_split(envp[i] + 5, ':');
	if (!splitted_path)
	{
		return (NULL);
	}
	return (splitted_path);
}

char	*get_cmd_path(char **envp, char *cmd_name)
{
	int		i;
	char	**splitted_path;
	char	*cmd_path;
	char	*full_cmd;
	char	slash[2];

	i = 0;
	slash[0] = '/';
	slash[1] = '\0';
	splitted_path = get_splitted_path(envp);
	if (!splitted_path)
		return (NULL);
	while (splitted_path[i])
	{
		cmd_path = ft_strjoin(splitted_path[i], slash);
		full_cmd = ft_strjoin(cmd_path, cmd_name);
		if (access(full_cmd, X_OK) == 0)
		{
			return (full_cmd);
		}
		i++;
	}
	return (NULL);
}

char	**get_cmd_args(char *cmd)
{
	int		i;
	char	**splitted_cmd;
	char	**args;

	i = 0;
	splitted_cmd = ft_split(cmd, ' ');
	while (splitted_cmd[i])
		i++;
	args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (splitted_cmd[i])
	{
		args[i] = splitted_cmd[i];
		i++;
	}
	args[i] = NULL;
	return (args);
}

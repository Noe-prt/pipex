/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:56:34 by nopareti          #+#    #+#             */
/*   Updated: 2024/12/02 18:48:43 by nopareti         ###   ########.fr       */
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
	if (!envp[i])
		return (NULL);
	splitted_path = ft_split(envp[i] + 5, ':');
	if (!splitted_path)
		return (NULL);
	return (splitted_path);
}

char	*get_cmd_path(char **envp, char *cmd_name)
{
	int		i;
	char	**splitted_path;
	char	*full_cmd;

	i = 0;
	splitted_path = get_splitted_path(envp);
	if (!splitted_path)
		return (NULL);
	while (splitted_path[i])
	{
		full_cmd = set_full_cmd(splitted_path[i], cmd_name);
		if (access(full_cmd, X_OK) == 0)
		{
			free_strs(splitted_path);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_strs(splitted_path);
	return (NULL);
}

char	*set_full_cmd(char *current_path, char *cmd_name)
{
	char	*full_cmd;
	char	*cmd_path;
	char	slash[2];

	slash[0] = '/';
	slash[1] = '\0';
	cmd_path = ft_strjoin(current_path, slash);
	full_cmd = ft_strjoin(cmd_path, cmd_name);
	free(cmd_path);
	return (full_cmd);
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
	if (!args)
	{
		free_strs(splitted_cmd);
		return (NULL);
	}
	i = 0;
	while (splitted_cmd[i])
	{
		args[i] = splitted_cmd[i];
		i++;
	}
	args[i] = NULL;
	free(splitted_cmd);
	return (args);
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

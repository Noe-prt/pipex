/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:25:33 by nopareti          #+#    #+#             */
/*   Updated: 2024/11/29 12:25:33 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	p_fd[2];
	pid_t	pid;
	int	f1;
	int	f2;

	if (argc != 5)
		exit(0); // args error
	if (pipe(p_fd) == -1)
		exit(0); // pipe error
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (!f1 || !f2)
	{
		perror("Fd Error");
		exit(0);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE); // fork error
	if (!pid)
		child_process(f1, argv[2], p_fd, envp);
	parent_process(f2, argv[3], p_fd, envp);
}

void	child_process(int f1, char* cmd, int p_fd[2], char **envp)
{
	dup2(f1, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	close(f1);
	if (!exec_cmd(cmd, envp))
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	exit(1);
}

void parent_process(int f2, char *cmd, int p_fd[2], char **envp)
{
	dup2(p_fd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(p_fd[1]);
	close(f2);
	if (!exec_cmd(cmd, envp))
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	exit(1);
}

char *get_cmd_path(char **envp)
{
	int	i;
	char	slash[2];
	char	**splitted_path;
	char	*cmd_path;
	char	*full_cmd;

	
	i = 0;
	slash[0] = '/';
	slash[1] = '\0';
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
	splitted_path = ft_split(envp[i] + 5, ':');
    if (!splitted_path)
	{
		free(splitted_path);
        return (NULL);
	}
	i = 0;
	while (splitted_path[i])
    {
		cmd_path = ft_strjoin(splitted_path[i], slash);
		full_cmd = ft_strjoin(cmd_path, cmd);
        if (access(full_cmd, X_OK) == 0)
		{
			free(splitted_path);
			free(cmd_path);
            return (full_cmd);
		}
        i++;
    }
	free(splitted_path);
	free(cmd_path);
	return (NULL);
}

char **get_cmd_args(char *cmd)
{
	int	i;
	char **splitted_cmd;
	char **args;

	i = 0;
	splitted_cmd = ft_split(cmd, ' ');
	while (splitted_cmd[i])
		i++;
	args = malloc(sizeof(char*) * (i + 1));
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

int exec_cmd(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = get_cmd_path(envp, cmd);
	cmd_args = get_cmd_args(cmd);
	if (cmd_path && cmd_args)
	{
		execve(cmd_path, cmd_args, envp);
		free(cmd_path);
		free(cmd_args);
		return (1);
	}
	free(cmd_path);
	free(cmd_args);
	return (0);
}

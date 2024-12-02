/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:25:33 by nopareti          #+#    #+#             */
/*   Updated: 2024/12/01 17:58:18 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	int		f1;
	int		f2;
	pid_t	pid;

	if (argc != 5)
		exit(-1);
	if (pipe(p_fd) == -1)
		exit(-1);
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (f1 == -1)
	{
		perror("pipex: file error");
		exit(-1);
	}
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child_process(f1, argv[2], p_fd, envp);
	parent_process(f2, argv[3], p_fd, envp);
}

void	child_process(int f1, char *cmd, int p_fd[2], char **envp)
{
	dup2(f1, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	close(f1);
	if (!exec_cmd(cmd, envp))
	{
		perror("pipex: command error");
		exit(-1);
	}
	exit(0);
}

void	parent_process(int f2, char *cmd, int p_fd[2], char **envp)
{
	dup2(p_fd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(p_fd[1]);
	close(f2);
	if (!exec_cmd(cmd, envp))
	{
		perror("pipex: command error");
		exit(-1);
	}
	exit(0);
}

int	exec_cmd(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_args = get_cmd_args(cmd);
	cmd_path = get_cmd_path(envp, cmd_args[0]);
	if (cmd_path && cmd_args)
	{
		execve(cmd_path, cmd_args, envp);
		return (1);
	}
	return (0);
}

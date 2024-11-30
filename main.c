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

int	main(int argc, char **argv)
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
		exit(0); // fork error
	if (!pid)
		child_process(f1, p_fd);
	parent_process(f2, p_fd);
}

void	child_process(int f1, int p_fd[2])
{
	char	*args[3] = {"ls", "-l", NULL};
	dup2(f1, STDIN_FILENO);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[0]);
	close(f1);
	execve("/bin/ls", args, NULL);
	exit(1);
}

void parent_process(int f2, int p_fd[2])
{
	char	*args[3] = {"wc", "-l", NULL};
	dup2(p_fd[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(p_fd[1]);
	close(f2);
	execve("/usr/bin/wc", args, NULL);
	exit(1);
}
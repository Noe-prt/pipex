/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:06:34 by nopareti          #+#    #+#             */
/*   Updated: 2024/11/27 11:06:34 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//   ./pipex infile "ls -l" "wc -l" outfile

#include "pipex.h"


int	main(int argc, char **argv)
{
	int	in_fd;
	int	out_fd;
	int	pipe_fd[2];
	char *grep_args[] = {"grep", "awawawa", NULL};
	char *wc_args[] = {"wc", "-l", NULL};
	pid_t pid1;
	pid_t pid2;

	if (!check_args(argc, argv))
	{
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
    {
        in_fd = open(argv[1], O_RDONLY);
        if (in_fd == -1)
        {
            perror("Error: Can't open infile");
            exit(EXIT_FAILURE);
        }
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execve("/usr/bin/grep", grep_args, NULL);
    }
	pid2 = fork();
	if (pid2 == 0)
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
        out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd == -1)
        {
            perror("Error: Can't open outfile");
            exit(EXIT_FAILURE);
        }
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
        execve("/usr/bin/wc", wc_args, NULL);
    }
	close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    exit(EXIT_SUCCESS);
}

int	check_args(int argc, char **argv)
{
	int	fd;
	if (argc != 5)
		return (0);
	if (access(argv[1], R_OK) == -1)
	{
		perror("Error: Can't read infile");
		return (0);
	}
	if (access(argv[4], W_OK) == -1)
	{
	 	fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("Error: Can't write to outfile");
			return (0);
		}
		close(fd);
	}
	return (1); // Tout est OK
}
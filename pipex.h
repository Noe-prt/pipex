/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:09:47 by nopareti          #+#    #+#             */
/*   Updated: 2024/11/27 12:09:47 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Libft/libft.h"

void parent_process(int f2, char *cmd, int p_fd[2], char **envp);
void	child_process(int f1, char* cmd, int p_fd[2], char **envp);
int	exec_cmd(char *cmd, char **envp);
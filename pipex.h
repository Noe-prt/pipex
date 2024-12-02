/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nopareti <nopareti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:09:47 by nopareti          #+#    #+#             */
/*   Updated: 2024/12/01 17:59:03 by nopareti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Libft/libft.h"

void	parent_process(int f2, char *cmd, int p_fd[2], char **envp);
void	child_process(int f1, char *cmd, int p_fd[2], char **envp);
int		exec_cmd(char *cmd, char **envp);
char	**get_splitted_path(char **envp);
char	*get_cmd_path(char **envp, char *cmd_name);
char	*set_full_cmd(char *current_path, char *cmd_name);
char	**get_cmd_args(char *cmd);
void	free_strs(char **strs);

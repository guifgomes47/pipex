/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhfer <guilhfer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:42:33 by guilhfer          #+#    #+#             */
/*   Updated: 2022/11/28 15:14:25 by guilhfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define PIPEX_ERROR "pipex: "
# define DIR_ERROR ": No such file or directory"
# define CMD_ERROR ": command not found"

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
}			t_args;

void		check_args(char **argv);
char		**get_path(char **envp);
void		free_split(char **ptr);
void		errors(t_args *args, int err_code, char *argv);
void		errors_param(t_args *args, char **cmd_args, char *path,
				int err_code);
char		*default_command_path(char *cmd);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhfer <guilhfer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:22:55 by guilhfer          #+#    #+#             */
/*   Updated: 2022/11/28 14:33:42 by guilhfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_split(char **ptr)
{
	int	i;

	if (ptr != NULL)
	{
		i = -1;
		while (ptr[++i])
			free(ptr[i]);
		free(ptr);
	}
}

char	*argv_checker(t_args *args, int err_code)
{
	char	*err_arg;

	if (err_code < 0)
		err_arg = args->argv[2];
	else
		err_arg = args->argv[3];
	return (err_arg);
}

void	errors_param(t_args *args, char **cmd_args, char *path, int err_code)
{
	char	*err_arg;

	err_arg = argv_checker(args, err_code);
	free_split(cmd_args);
	if (err_code == 1 || err_code == -1)
	{
		write(2, PIPEX_ERROR, ft_strlen(PIPEX_ERROR));
		write(2, err_arg, ft_strlen(err_arg));
		write(2, CMD_ERROR, ft_strlen(CMD_ERROR));
		write(2, "\n", 1);
		free_split(args->path);
		exit(127);
	}
	if (err_code == 2)
	{
		perror("Error in execution\n");
		free(path);
		free_split(args->envp);
	}
	if (err_code == 3)
	{
		ft_putendl_fd("Permission denied", 2);
		free_split(args->path);
		exit(126);
	}
}

void	errors(t_args *args, int err_code, char *argv)
{
	free_split(args->path);
	if (err_code == 0)
		perror("Error\n");
	if (err_code == 1)
		perror("Error with opening the pipe\n");
	if (err_code == 2)
		perror("An error occoured with fork\n");
	if (err_code == 3)
	{
		write(2, PIPEX_ERROR, ft_strlen(PIPEX_ERROR));
		write(2, argv, ft_strlen(argv));
		write(2, DIR_ERROR, ft_strlen(DIR_ERROR));
		write(2, "\n", 1);
	}
	if (err_code == 4)
		perror("Failed finding command path\n");
	if (err_code == 5)
		perror("Failed finding command path\n");
	exit(EXIT_FAILURE);
}

void	check_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], " ", ft_strlen(" ")) == 0)
		{
			ft_putendl_fd("Error: Empty strings are not arguments.", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

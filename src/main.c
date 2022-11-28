/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhfer <guilhfer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:12:43 by guilhfer          #+#    #+#             */
/*   Updated: 2022/11/28 15:11:27 by guilhfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <pipex.h>

char	*find_command_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/') != NULL && access(cmd, F_OK) == 0)
	{
		cmd_path = ft_strdup(cmd);
		return (cmd_path);
	}
	if (default_command_path(cmd) != NULL)
		return (default_command_path(cmd));
	while (path && path[i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (cmd_path == NULL)
		{
			i++;
			continue ;
		}
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

static void	parent_process(t_args *args, int fd[2])
{
	int		file;
	char	**cmd_args;
	char	*cmd_path;

	file = open(args->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file == -1)
		errors(args, 3, args->argv[4]);
	dup2(fd[0], 0);
	dup2(file, 1);
	close(file);
	close(fd[0]);
	close(fd[1]);
	cmd_args = ft_split_cmd(args->argv[3], ' ');
	if (cmd_args == NULL)
		ft_putendl_fd("Argument do not exist", 2);
	cmd_path = find_command_path(args->path, cmd_args[0]);
	if (cmd_path == NULL)
		errors_param(args, cmd_args, cmd_path, 1);
	if (access(cmd_path, X_OK) != 0)
		errors_param(args, cmd_args, cmd_path, 3);
	if (execve(cmd_path, cmd_args, args->envp) == -1)
		errors_param(args, cmd_args, cmd_path, 2);
}

static void	child_process(t_args *args, int fd[2])
{
	int		file;
	char	**cmd_args;
	char	*cmd_path;

	file = open(args->argv[1], O_RDONLY);
	if (file == -1)
		errors(args, 3, args->argv[1]);
	dup2(file, 0);
	dup2(fd[1], 1);
	close(file);
	close(fd[0]);
	close(fd[1]);
	cmd_args = ft_split_cmd(args->argv[2], ' ');
	if (cmd_args == NULL)
		errors(args, 0, args->argv[1]);
	cmd_path = find_command_path(args->path, cmd_args[0]);
	if (cmd_path == NULL)
		errors_param(args, cmd_args, cmd_path, -1);
	if (access(cmd_path, X_OK) != 0)
		errors_param(args, cmd_args, cmd_path, 3);
	if (execve(cmd_path, cmd_args, args->envp) == -1)
		errors_param(args, cmd_args, cmd_path, 2);
}

static void	pipex(t_args *args)
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		errors(args, 1, args->argv[0]);
	id = fork();
	if (id == -1)
		errors(args, 2, args->argv[0]);
	if (id == 0)
		child_process(args, fd);
	else
	{
		waitpid(-1, NULL, WNOHANG);
		parent_process(args, fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	if (argc != 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		return (1);
	}
	check_args(argv);
	args.argc = argc;
	args.argv = argv;
	args.envp = envp;
	args.path = get_path(envp);
	pipex(&args);
	free_split(args.path);
	return (0);
}

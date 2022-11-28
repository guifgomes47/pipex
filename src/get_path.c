/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhfer <guilhfer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:09:57 by guilhfer          #+#    #+#             */
/*   Updated: 2022/11/27 19:41:06 by guilhfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	add_slash(char **splitted_path)
{
	char	*temp;
	int		i;

	i = 0;
	while (splitted_path[i] != NULL)
	{
		temp = splitted_path[i];
		splitted_path[i] = ft_strjoin(temp, "/");
		if (splitted_path == NULL)
		{
			splitted_path[i] = temp;
			return (1);
		}
		free(temp);
		i++;
	}
	return (0);
}

static char	*extract_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			path = ft_strdup(&envp[i][5]);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	char	*path;
	char	**splitted_path;

	if (envp == NULL)
		return (NULL);
	path = extract_path(envp);
	if (path != NULL)
	{
		splitted_path = ft_split(path, ':');
		free(path);
		if (add_slash(splitted_path) == 1)
		{
			free_split(splitted_path);
			return (NULL);
		}
		return (splitted_path);
	}
	return (NULL);
}

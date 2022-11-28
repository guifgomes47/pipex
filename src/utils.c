/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhfer <guilhfer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:48:51 by guilhfer          #+#    #+#             */
/*   Updated: 2022/11/28 15:11:37 by guilhfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*default_command_path(char *cmd)
{
	char	*def_path;

	def_path = ft_strjoin("/bin/", cmd);
	if (access(def_path, F_OK) == 0)
		return (def_path);
	else
		free(def_path);
	return (NULL);
}

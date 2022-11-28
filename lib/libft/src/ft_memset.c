/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhfer <guilhfer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:16:47 by guilhfer          #+#    #+#             */
/*   Updated: 2022/05/19 17:08:27 by guilhfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The memset() function fills the first n bytes of the memory area pointed to
by str with the constant byte c. */

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*set;

	i = 0;
	set = str;
	while (i < n)
	{
		((char *)set)[i] = c;
		i++;
	}
	return (str);
}

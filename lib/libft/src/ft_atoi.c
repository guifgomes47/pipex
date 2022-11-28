/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhfer <guilhfer@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:39:46 by guilhfer          #+#    #+#             */
/*   Updated: 2022/05/19 16:58:14 by guilhfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The atoi() function converts the initial portion of the string
pointed to by nptr to int. */

int	ft_isspace(int n)
{
	if ((n == '\n') || (n == '\t') || (n == '\r') || (n == '\v') || (n == '\f')
		|| (n == ' '))
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sin;
	int	res;

	i = 0;
	sin = 1;
	res = 0;
	while (ft_isspace(nptr[i]))
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		{
			sin *= -1;
		}
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = (res * 10) + (nptr[i++] - '0');
	}
	return (res * sin);
}

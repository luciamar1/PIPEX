/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:00:23 by lucia-ma          #+#    #+#             */
/*   Updated: 2023/02/24 15:00:23 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"

char	*ft_strjoinpip(char const *s1, char const *s2)
{
	char	*s;
	int		l;

	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = malloc(l * sizeof(char) + 1);
	if (s == NULL)
		return (NULL);
	while (*s1)
		*s++ = *s1++;
	*s++ = 47;
	while (*s2)
		*s++ = *s2++;
	*s = 0;
	return (s - l);
}

char	*ft_find_paths(char **large, char *small)
{
	size_t	lsmall;

	lsmall = ft_strlen(small);
	while (*large)
	{
		if (!ft_strncmp(*large, small, lsmall))
			return (*large);
	large++;
	}
	return (NULL);
}

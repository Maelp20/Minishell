/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:13:32 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/27 20:19:55 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstr;
	size_t	i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	newstr = malloc(sizeof(*s1) * (i + 1));
	if (!newstr)
		return (exit(EXIT_FAILURE), NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = 0;
	return (newstr);
}

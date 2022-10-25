/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:13:46 by mpignet           #+#    #+#             */
/*   Updated: 2022/09/26 13:45:51 by mpignet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	ft_join(char *dest, char const *s1, char const *s2)
{
	int	i;

	i = 0;
	while (*s1)
	{
		dest[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		dest[i] = *s2;
		s2++;
		i++;
	}
	return ;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*dest;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = 0;
		i++;
	}
	ft_join(dest, s1, s2);
	dest[len] = '\0';
	return (dest);
}

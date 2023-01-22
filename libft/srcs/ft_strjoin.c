/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:13:46 by mpignet           #+#    #+#             */
/*   Updated: 2023/01/22 15:23:37 by yanthoma         ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*dest;
	int		len;

	if (!s2)
		s2 = malloc(sizeof(char));
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < len)
		dest[i] = 0;
	ft_join(dest, s1, s2);
	dest[len] = '\0';
	return (dest);
}

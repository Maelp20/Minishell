/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:28:34 by yanthoma          #+#    #+#             */
/*   Updated: 2022/05/30 13:28:42 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*stash;
	static char		buffer[BUFFER_SIZE + 1];
	ssize_t			readed;
	char			*line_to_return;

	readed = 1;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1024)
		return (NULL);
	stash = NULL;
	stash = ft_strjoin1(stash, buffer);
	while (readed && !ft_new_line(stash))
	{
		if (!stash)
			return (NULL);
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (ft_free(stash));
		buffer[readed] = '\0';
		if (!readed && !stash[0])
			return (ft_free(stash));
		stash = ft_strjoin1(stash, buffer);
	}
	line_to_return = clear_line_from_stash (stash, buffer);
	return (free (stash), line_to_return);
}

char	*clear_line_from_stash(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	j = -1;
	while (++j < i && stash[j])
		temp[j] = stash[j];
	temp[j] = '\0';
	j = 0;
	while (stash[i] && buffer[j])
		buffer[j++] = stash[i++];
	buffer[j] = '\0';
	return (temp);
}

//  int	main(void)
//  {
//  	int		fd;
//  	char	*line;
//  	fd = open("../../maps/first_map.ber", O_RDONLY);
// 	while (1)
//  	{
// 		line = get_next_line(fd);
//  		printf("%s", line);
//  		if (line == NULL)
//  			break ;
// 		free(line);	
//  	}
// 	// printf("\n\n");
// 	// fd = open("get_next_line.h", O_RDONLY);
// 	// 	line = get_next_line(fd);
// 	// 	printf("%s", line);
// 	// 	free(line);

//  	return (0);
//  }

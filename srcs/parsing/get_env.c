/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:17:27 by yanthoma          #+#    #+#             */
/*   Updated: 2022/12/06 17:24:34 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_envp	*lstnew_env(char **content)
{
	t_envp  *dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->var = content;
	dest->var[0]= ft_strjoin(dest->var[0], "=");
	dest->next = NULL;
	return (dest);
}

// void	lstadd_back_env(t_envp **lst, t_envp *new)
// {
// 	if (*lst == ((void *)0))
// 		*lst = new;
// 	else
// 		lstadd_back_env(&((*lst)->next), new);
// }

// void	get_env(char **envi, t_data *data)
// {
// 	int i;

// 	data->envp = NULL;
// 	i = -1;
// 	while (envi[++i])
// 		lstadd_back_env(&data->envp ,lstnew_env(ft_split(envi[i], '=')));
// }


char **split_at_first_equal(const char *input)
{
  char **output;
  char * equal_pos;
  size_t first_len;
  size_t second_len;
  
  output = malloc(sizeof(char *) * 3);
  equal_pos = ft_strchr(input, '=');
  if (equal_pos)
  {
    first_len = equal_pos - input;
    printf("first len %ld\n", first_len);
    output[0] = malloc(first_len + 1);
    ft_strlcpy(output[0], input, first_len);
    output[0][first_len] = '\0';
    second_len = strlen(input) - first_len - 1;
    output[1] = malloc(second_len + 1);
    ft_strlcpy(output[1], equal_pos + 1, second_len);
    output[1][second_len] = '\0';
    output[2] = NULL;
    return (output);
  }
  else
    return (NULL);
}

void get_env(char **envi, t_data *data)
{
    int i;
    t_envp *node;
    t_envp **tail;

    i = 0;
    data->envp = NULL;
    tail = &data->envp;

    while (envi[i])
    {
        node = lstnew_env(split_at_first_equal(envi[i]));
        if (!node)
            continue;
        *tail = node;
        tail = &node->next;
        i++;
    }
}

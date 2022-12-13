/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:17:27 by yanthoma          #+#    #+#             */
/*   Updated: 2022/12/13 15:55:16 by yanthoma         ###   ########.fr       */
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




void copy_split_first_equal(size_t len, char **dest, char *input)
{
  *dest = malloc(len + 1);
  ft_strlcpy(*dest, input, len);
  (*dest)[len] = '\0';
}


//protect the malloc otherwise it's a fail
char **split_at_first_equal(char *input)
{
  char **output;
  char *equal_pos;
  size_t first_len;
  size_t second_len;

  output = malloc(sizeof(char *) * 3);
  equal_pos = ft_strchr(input, '=');
  if (equal_pos)
  {
    first_len = equal_pos - input + 1;
    copy_split_first_equal(first_len, &output[0], input);
    second_len = ft_strlen(input) - first_len + 1;
    copy_split_first_equal(second_len, &output[1], equal_pos + 1);
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

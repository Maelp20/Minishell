/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:17:27 by yanthoma          #+#    #+#             */
/*   Updated: 2023/01/02 16:06:27 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"



void print_env(t_envp *list)
{
    t_envp *current = list;
    while (current)
    {
        printf("%s%s\n", current->var[0],current->var[1]);
        current = current->next;
    }
}


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

t_envp *get_env(char **envi)
{
    int i;
    t_envp *head;
    t_envp *node;
    t_envp **tail;

    i = 0;
    head = NULL;
    tail = &head;

    while (envi[i])
    {
        node = lstnew_env(split_at_first_equal(envi[i]));
        if (!node)
            return NULL;
        *tail = node;
        tail = &node->next;
        i++;
    }
    printf("%s%s\n", head->var[0],head->var[1]);
    return head;
}

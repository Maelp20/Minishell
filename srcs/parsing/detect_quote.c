/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 08:25:04 by yanthoma          #+#    #+#             */
/*   Updated: 2022/12/07 21:39:55 by yanthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_sep(char c)
{
	if (c == '\"')
		return (3);
	else if ( c == '\'')
		return (2);
	else if ( c == ' ')
		return (1);
	return (0);
}

int	split_dbq(char *input, int i, t_tok **lst)
{
	int		j;
	char	*tmp;
	
	j = i;
	while (input[j + 1] && is_sep(input[j]) != 3)
		j++;
	if (input[j] != '\"' && input [j + 1] =='\0')
		return (-2);
	tmp = malloc(sizeof(char) * (j - i + 1));
	if (!tmp)
		return (-2);
	j = -1;
	i--;
	while(is_sep(input[++i]) != 3)
		tmp[++j] = input[i];
	tmp[++j] = '\0';
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), ++i);
} 

int	split_with_sq_dollar(char *input, int i, t_tok **lst)
{
	int j;
	char *tmp;

	j = i;
	while (input[j] != '\'')
	{
		printf("split dollar %c\n", input[j]);
		j++;
	}
	printf("split dollar %c\n", input[j]);
	printf("j = %d\n", j - i + 2);
	tmp = malloc(sizeof(char) * (j - i + 3));
	if (!tmp)
		return(-2);
	j = 0;
	i--;
	tmp[j] = '\'';
	while (input[++i] && input[i] != '\'')
		tmp[++j] = input[i];
	tmp[++j] = '\'';
	tmp[++j] = '\0';
	printf("%s\n", tmp);
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), ++i);
}

int	split_sq(char *input, int i, t_tok **lst)
{
	int		j;
	char	*tmp;
	
	if (input[i] == '$')
		return (split_with_sq_dollar(input, i, lst));
	j = i;
	while (is_sep(input[j]) != 2 && input[j + 1]) 
		j++;
	if (input[j] != '\'' && input [j + 1] =='\0')
		return (-2);
	tmp = malloc(sizeof(char) * (j - i + 1));
	if (!tmp)
		return (-2);
	j = -1;
	i--;
	while(is_sep(input[++i]) != 2)
		tmp[++j] = input[i];
	tmp[++j] = '\0';
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), ++i);
}

int	split_space(char *input, int i, t_tok **lst)
{
	int		j;
	char	*tmp;
	
	j = i;
	while (input[j] && !is_sep(input[j]))
		j++;
	tmp = malloc(sizeof(char) * (j - i + 1));
	if (!tmp)
		return (-2);
	j = -1;
	i--;
	while(input[++i] && !is_sep(input[i]))
		tmp[++j] = input[i];
	tmp[++j] = '\0';
	lstadd_back_token(lst, lstnew_token(tmp));
	return (free(tmp), --i);
}
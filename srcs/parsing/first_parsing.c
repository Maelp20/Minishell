#include "exec.h"

void	tok_del_one(t_tok *lst)
{
	if (lst->token)
		free(lst->token);
	if (lst)
		free(lst);
}

t_tok	*lstnew_token(char *content)
{
	t_tok  *dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->token = ft_strdup(content);
	dest->next = NULL;
	dest->prev = NULL;
	return (dest);
}

void	lstadd_back_token(t_tok **lst, t_tok *new)
{
	if (!(*lst))
		*lst = new;
	else
	{
		if ((*lst)->next == NULL)
				new->prev = *lst;
			lstadd_back_token(&((*lst)->next), new);
	}
}

t_tok	*ft_lstlast_tok(t_tok *lst)
{
	if (!lst)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (ft_lstlast_tok(lst->next));
}

t_tok	*init_token_lst(char *input, t_data	**lst)
{
	int	i;
	t_tok	*tok_lst;
	
	(void)lst;
	i = 0;
	tok_lst = NULL;
	while(i >= 0 && input[i])
	{
		if (i >= 0 && input[i] && is_sep(input[i]) != 1)
		 	i = split_space(input, i, &tok_lst);
		i++;
	}
	if (i < 0)
		clean_parsing(&tok_lst, lst);
	return (tok_lst);
}
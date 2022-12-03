#include "exec.h"

t_tok	*lstnew_token(char *content)
{
	t_tok  *dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->token = ft_strdup(content);
	dest->next = NULL;
	return (dest);
}

void	lstadd_back_token(t_tok **lst, t_tok *new)
{
	if (!(*lst))
		*lst = new;
	else
		lstadd_back_token(&((*lst)->next), new);
}

t_tok	*init_token_lst(char *input, t_data	**lst)
{
	int	i;
	t_tok	*tok_lst;
	
	(void)lst;
	i = 0;
	tok_lst = NULL;
	while(input[i])
	{
		if (input[i] == '\"')
			i = split_dbq(input, ++i, &tok_lst);
		i++;
	}
			while(tok_lst)
			{
	 			printf("%s\n", tok_lst->token);
	 			tok_lst = tok_lst->next;
			}
	return (tok_lst);
}
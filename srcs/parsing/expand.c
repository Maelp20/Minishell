#include "exec.h"

int	is_char_var(char c)
{

}

char *expand_from(char *token, t_data *data)
{
	int		len;
	int		i;
	char	*expanded;

	i = 0;
	len = 0;
	while (token[i] && token[i] != '$')
		len = ++i;
	
	printf(" expand from %c\n", token[i]);
	return ("filled");
}

void	expand(t_tok **lst, t_data **data)
{
	char	*temp;
	t_tok	*tmp;
	int		i;

	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while(tmp->token[0] != '\'' && tmp->token[i])
		{
			if (tmp->token[i] == '$')
			{
				temp = ft_strdup(tmp->token);
				//free (tmp->token);
				tmp->token = expand_from(temp, *data);
				printf("expand temp %s\n", temp);
				break;
			}
			i++;
		}
		tmp = tmp->next;
	}
}
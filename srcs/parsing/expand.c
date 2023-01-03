#include "exec.h"


void	expand(t_tok **lst, t_data **data)
{
	char	*temp;
	t_tok	*tmp;
	
	tmp = *lst;
	while (tmp)
	{
		if (tmp->token[1] == '$')
		{
			temp = ft_strdup(tmp->token);
			temp += 2;
			//free (tmp->token);
			printf("expand temp %s\n", temp),
		}
	}
}
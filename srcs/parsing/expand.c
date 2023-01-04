#include "exec.h"

int	is_char_var(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char *expand_from(char *token, t_data *data)
{
	int		len;
	int		len_env;
	int		i;
	char	*expanded;
	t_envp	*tmp;

	i = 0;
	len = 0;
	while (token[i] && token[i] != '$')
		len = ++i;
	while (token[++i] && is_char_var(token[i]))
		len_env = i - len;
	//token = token + len + 1;
	tmp = data->envp;
	printf("%d\n", len_env);
	while(tmp)
	{
		if (!ft_strncmp(token + len + 1, tmp->var[0], len_env))
			break;
		//printf("token = %s envp = %s\n", token + len + 1, tmp->var[0]);
		tmp = tmp->next;
	}
	expanded = malloc(sizeof(char) * (len + ft_strlen(tmp->var[1]) + 1));
	i = -1;
	printf("token = %s envp = %s\n", token + len + 1, tmp->var[1]);
	while (++i < len)
		expanded[i] = token[i];
	int j = -1;
	while (tmp->var[1][++j])
		expanded[++i] = tmp->var[1][j];
	expanded[++i] = '\0';
	//printf("token + len = %s\n", token);
	//printf(" expand from %c\n", token[i]);
	return (expanded);
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
				free (tmp->token);
				tmp->token = expand_from(temp, *data);
				free(temp);
				break;
			}
			i++;
		}
		tmp = tmp->next;
	}
}
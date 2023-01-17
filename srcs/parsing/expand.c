#include "exec.h"

int	is_char_var(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||  c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


int len_env(char *str, int i)
{
	int len;

	len = 0;
	while (is_char_var(str[i]))
	{
		i++;
		len++;
	}
	printf("is char %c\n", str[i]);
	return(len);
}

int	len_expanded(char *str, int i, int len_env, t_data *data)
{
	t_envp *tmp;
	int len;
	printf("%c\n", str[i]);
	printf("i =  %d\n" , i);
	int j = 0;
	len = 0;
	tmp = data->envp;
	while (j < len_env)
	{
		printf("len expanded %d %c" ,j,  str[j + i]);
		j++;
	}
	printf("\n");
	while(tmp)
	{
		if (!ft_strncmp(str + i, tmp->var[0], len_env))
			break;
		//printf("token = %s envp = %s\n", token + len + 1, tmp->var[0]);
		tmp = tmp->next;
	}
	if (tmp)
		len += (int)ft_strlen(tmp->var[1]);
	return (len);
}

int	trigger_expand(char *str, int i, t_data *data)
{
	int		dbl;
	int		sq;
	int		len;
	
	len = 0;
	sq = 2;
	dbl = 2;
	while (str[i])
	{
		printf("str[i]= %c\n", str[i]);
		if (str[i] == '\"')
			dbl++;
		if (str[i] == '\'' && !(dbl % 2))
			sq++;
		if(str[i] == '$' && !(sq % 2) && str[i + 1] != '\"')
		{
			printf("$ = %c\n", str[i]);
			len += len_expanded(str, i + 1, len_env(str, i + 1), data);
			i += len_env(str, i + 1) + 1;
			printf(" trig i = %d\n", i);
			printf(" trig len = %d\n", len);
		}
		len++;
		i++;
	}
	printf("len = %d\n", len);
	return(len);
}

char *expand_from(char *token, t_data *data)
{
	int i;
	i = 0;
	i = trigger_expand(token, i, data);
	return(NULL);
	printf("%d\n", i);

}

void	expand(t_tok **lst, t_data **data)
{
	int		dbl;
	int		sq;
	int		i;
	char	*temp;
	t_tok	*tmp;

	sq = 2;
	dbl = 2;
	tmp = *lst;
	while (tmp)
	{
		i = -1;
		while (tmp->token[++i])
		{
			if (tmp->token[i] == '\"')
				dbl++;
			if (tmp->token[i] == '\'' && !(dbl % 2))
				sq++;
			if(tmp->token[i] == '$' && !(sq % 2))
			{
				temp = ft_strdup(tmp->token);
				free (tmp->token);
				tmp->token = expand_from(temp, *data);
				free(temp);
				break;
			}
		}
		tmp = tmp->next;
	}
}
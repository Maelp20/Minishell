#include "../includes/minishell.h"
#include "../libft/libft.h"


t_envp	*lstnew(char **content)
{
	t_envp	*dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->var = content;
	dest->var[0]= ft_strjoin(dest->var[0], "=");
	dest->next = NULL;
	return (dest);
}

void	lstadd_back(t_envp **lst, t_envp *new)
{
	if (*lst == ((void *)0))
		*lst = new;
	else
		lstadd_back(&((*lst)->next), new);
}


void	get_env(char **envi, t_envp *envp)
{
	int i;

	
	i = -1;
	while (envi[++i])
	{

	lstadd_back(&envp ,lstnew(ft_split(envi[i], '=')));
	}	
}

int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;

	data = malloc(sizeof(data));
	(void)av;
	(void)ac;
	
	get_env(env, data->envp);
	while (ac > 0)
	{
		input = readline("Minishell>");
		if (input && *input)
			add_history(input);
		printf("%s\n",input);
		i++;
	}
}
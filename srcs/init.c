#include "../includes/minishell.h"
#include "../libft/libft.h"

void	free_array(char** array)
{
	int i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	init_struct(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->cmd = NULL;
	data->path = NULL;
	data->envp = NULL;
}

void	destroy_struct(t_data *data)
{
	while (data)
	{
		if (data->cmd)
			free(data->cmd);
		if (data->path)
			free_array(data->path);
		while (data->envp)
		{
			if (data->envp->var)
				free_array(data->envp->var);
			data->envp = data->envp->next;
		}
		free(data->envp);
		data = data->next;
	}
	free(data);
}


t_data	*lstnew_args(char *content)
{
	t_data  *dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->cmd = content;
	dest->next = NULL;
	return (dest);
}

void	lstadd_back_args(t_data **lst, t_data *new)
{
	//t_env *last = ft_last(lst);
	
	if (*lst == ((void *)0))
		*lst = new;
	else
		lstadd_back_args(&((*lst)->next), new);
		//lstadd_back_env(&((*lst)->prev), last);
}

void	init_args(t_data *data, char *arg)
{

	int i;
	char **tmp;
	
	data = NULL;
	i = 0;
	tmp = ft_split(arg, ' ');
	while (tmp[i])
	{
		lstadd_back_args(&data ,lstnew_args(tmp[i]));
		i++;
	}
}
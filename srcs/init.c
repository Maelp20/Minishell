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


void	init_args(t_data *data, char *arg)
{
	char 	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(arg,' ');
	while (tmp[i])
	{
		data->cmd = strdup(tmp[i]);
		data = data->next;
		i++;
	}
	free_array(tmp);
}
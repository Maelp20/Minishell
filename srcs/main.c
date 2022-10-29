#include "../includes/minishell.h"
#include "../libft/libft.h"



int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;

	data = malloc(sizeof(t_data));
	(void)av;
	(void)ac;
	
	get_env(env, data);
	// while(data->envp)
	// {
	// 	printf("%s\n %s\n", data->envp->var[0],data->envp->var[1] );
	// 	data->envp = data->envp->next;
	// }
	check_access(data);
	i = 0;
	while(data->path[i])
	{
		printf("%s\n", data->path[i]);
		i++;
	}
	while (ac > 0)
	{
		input = readline("Minishell>");
		if (input && *input)
			add_history(input);
		printf("%s\n",input);
		i++;
	}
}
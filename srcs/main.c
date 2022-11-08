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
	check_access(data);
	i = 0;
	while (ac > 0)
	{
		input = readline("Minishell>");
		if (input && *input)
		{
			
			add_history(input);
			init_args(data, input);
			while(data)
			{
				printf("%s success\n", data->cmd);
				data = data->next;
			}
			//is_in_quote(input);

		}
		printf("%s\n",input);
		i++;
	}
}
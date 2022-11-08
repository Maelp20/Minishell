#include "../includes/minishell.h"
#include "../libft/libft.h"



int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;
	t_data *tmp;

	(void)av;
	(void)ac;
	

	i = 0;
	while (ac > 0)
	{
		data = malloc(sizeof(t_data));
		get_env(env, data);
		check_access(data);
		input = readline("Minishell>");
		if (input && *input)
		{
			
			add_history(input);
			init_args(data, input);
			tmp = data;
			while(tmp)
			{
				printf("%s success\n", tmp->cmd);
				tmp = tmp->next;
			}
			//is_in_quote(input);

		}
		destroy_struct(data);
		i++;
	}
}
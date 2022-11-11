#include "../includes/minishell.h"
#include "../libft/libft.h"



int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;

	(void)av;
	(void)ac;
	
	

	i = 0;
	while (ac > 0)
	{

		input = readline("Minishell>");
		if (input && *input)
		{
			data = NULL;
			add_history(input);
			init_args(&data, input);
			get_env(env, data);
			get_path(data);
			printf("test\n");
			//is_in_quote(input);

		}
			while(data)
			{
	 			printf("%s\n", data->cmd);
	 			data = data->next;
			}	
		destroy_struct(data);
		i++;
	}
}
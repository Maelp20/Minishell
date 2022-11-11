#include "../includes/minishell.h"
#include "../libft/libft.h"



int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_data *data;

	(void)av;
	i = 0;
	while (ac > 0)
	{

		input = readline("Minishell>");
		if (input && *input)
		{
			if (ft_strncmp(input,"exit",4)  == 0)
				return(free(input),destroy_struct(data), exit(0), 0);
			data = NULL;
			add_history(input);
			init_args(&data, input);
			get_env(env, data);
			get_path(data);
			//is_in_quote(input);
		}
			while(data)
			{
	 			printf("%s\n", data->cmd);
	 			data = data->next;
			}
		free(input);
		destroy_struct(data);
		i++;
	}
}
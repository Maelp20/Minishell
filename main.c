#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


int main(int ac, char **av, char **env)
{
	char *input;
	int i =0;
	
	(void)av;
	(void)env;
	(void)ac;
	while (ac > 0)
	{
		input = readline("Minishell>");
		if (input && *input)
			add_history(input);
		printf("%s\n",input);
		i++;
	}
}
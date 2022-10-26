#include "../includes/minishell.h"
#include "../libft/libft.h"


char **parse_env(char *line)
{
	//char **str;
	printf("%s\n", line + (ft_strlen(line) - ft_strlen(ft_strchr(line, '='))) +1);
	//return (str);
	return (NULL);
}
void	get_env(char **envi, t_env *envp)
{
	int i;
	(void)envp;
	i = -1;
	while (envi[++i])
	{
			//envp->env = 
			parse_env(envi[i]);
		//envp = envp->next;
	}

}

int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_env *envp;

	envp = NULL;
	(void)av;
	(void)ac;
	get_env(env, envp);
	while (ac > 0)
	{
		input = readline("Minishell>");
		if (input && *input)
			add_history(input);
		printf("%s\n",input);
		i++;
	}
}
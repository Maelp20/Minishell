#include "../includes/minishell.h"
#include "../libft/libft.h"


// char **parse_env(char *line)
// {
// 	char **str;
// 	int lim; 
// 	int i;
// 	int j;

// 	lim = ft_strlen(line) - ft_strlen(ft_strchr(line, '=')) +1;
// 	printf("%d\n", lim);
// 	j = -1;
// 	str = malloc(sizeof(char *) * 2);
// 	while (++j < 2)
// 	{
// 		i = -1;
// 		str[j] = malloc(sizeof(char) * (lim +1));
// 		while (++i < lim)
// 		{
// 			str[j][i] = line[i];
// 		}
// 		printf("%s\n", str[j]);
// 		free(str[j]);		
// 	}
// 	free(str);
// 	return (NULL);
// }


void	parse_env(char *line, t_envp *env)
{
	
	env->var = ft_split(line, '=');
	env->var[0] = ft_strjoin(env->var[0], "=");
	printf("%s\n%s\n", env->var[0], env->var[1]);
}

void	get_env(char **envi, t_envp *envp)
{
	int i;

	i = -1;
	while (envi[++i])
	{
		ft_lstadd_back(&envp ,ft_lstnew(ft_split(envi[i], '=')));
		//envp->var[0] = ft_strjoin(envp->var[0], "=");
	}
	while(envp)
	{
		printf("%s %s\n", envp->var[0],envp->var[1] );
		envp = envp->next;
	}

}

int main(int ac, char **av, char **env)
{
	char *input;
	int i = 0;
	t_envp *envp;

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
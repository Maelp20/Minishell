#include "exec.h"

int	is_to_split(char c)
{
	if ( c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

// void	replace_node(t_tok **lst, t_tok **tmp, t_tok *node)
// {
// 	//find the node to replace
// 	printf("replace node\n");
// 	while (lst && strcmp((*lst)->token, node->token))
// 	{
// 		printf("lst = %s\n", (*lst)->token);
// 		printf("node = %s\n", node->token);
// 		(*lst) = (*lst)->next;
// 	}
// 	//set the node to the first of tmp
// 	(*lst) = (*tmp);
// 	//go to the last node of tmp
// 	while ((*tmp) && (*tmp)->next)
// 		(*tmp) = (*tmp)->next;
// 	//set the end of tmp to the next
// 	if (*tmp)
// 		*tmp = (*lst)->next;
// 	//free the node to replace
// 	free(*lst);
// }

// int	split_pipe_and_chev(char *token, t_tok **lst)
// {
// 	int	j;
// 	int i;
// 	char *tmp;
	
// 	j = i;

// 	while(token[j] && !is_to_split(token[j]))
// 		j++;

// 	tmp = ft_calloc(sizeof(char), (j - i + 2));
// 	if (!tmp)
// 		return (-2);
// 	j = -1;
// 	i--;
// 	while(!is_to_split(token[++i]))
// 	{
// 			tmp[++j] = token[i];
// 	}
// 	if (is_to_split(token[i]))
// 		tmp[++j] = token[i];

// 	tmp[++j] = '\0';
// 	lstadd_back_token(lst, lstnew_token(tmp));	
// 	return(free (tmp), i);
// }


// void	clean_token_lst(t_tok **lst)
// {
// 	int			i;
// 	t_tok	*tmp;

// 	// while(*lst)
// 	// {
// 	//  	printf("CLEAN %s\n", (*lst)->token);
// 	//  	*lst = (*lst)->next;
// 	// }
// 	while ((*lst))
// 	{
// 		i = 0;
// 		tmp = NULL;
// 		while((*lst)->token[i])
// 		{
// 			if (is_to_split((*lst)->token[i]))
// 			{
// 				tmp = split_string((*lst)->token);
// 				break;
// 			}
// 			i++;
// 		}
// 		while(tmp)
// 		{
// 			printf("tmp end = %s\n", tmp->token);
// 			tmp = tmp->next;
// 		}
// 		//  if (tmp)
// 		//  	replace_node(lst, &tmp, *lst);
// 		(*lst) = (*lst)->next;
// 	}
// 	while(*lst)
// 	{
// 		printf("clean - %s\n", (*lst)->token);
// 		*lst = (*lst)->next;
// 	}
// }

t_tok *split_string(const char *str)
{
t_tok *head = NULL;
t_tok *current = NULL;

// Initialize the current token to an empty string
current = malloc(sizeof(t_tok));
current->token = malloc(1);
current->token[0] = '\0';
current->next = NULL;
head = current;

int i = 0;
while (str[i])
{
    // Check if the current character is one of the delimiters
    if (str[i] == '|' || str[i] == '>' || str[i] == '<')
    {
        // If the current token is an empty string (indicating that the input string consists only of delimiter characters), create a new token for the first delimiter character
        if (current->token[0] == '\0')
        {
            current->token[0] = str[i];
            current->token[1] = '\0';
            i++;
            continue;
        }
        // If the current token is an empty string (indicating that the previous character was also a delimiter),
		// skip the current character
        if (current->token[0] == '\0')
        {
            i++;
            continue;
        }
        // Create a new token for the delimiter
        current->next = malloc(sizeof(t_tok));
        current = current->next;
        current->token = malloc(2);
        current->token[0] = str[i];
        current->token[1] = '\0';
        current->next = NULL;
    }
    else
    {
        // If the current character is not a delimiter, add it to the current token
        int len = strlen(current->token);
        current->token = realloc(current->token, len + 2);
        current->token[len] = str[i];
        current->token[len + 1] = '\0';
    }
    i++;
}
return head;
}

void	clean_token_lst(t_tok **lst)
{
	(void)lst;
	
    // Split the string "|J>>e>jesuis<<lol>" into tokens
    t_tok *list = split_string("|J>>e>jesuis<<lol>");

    // Allocate memory for the current token in the list
    t_tok *current = malloc(sizeof(t_tok));

    // Print the tokens in the list
    for (current = list; current; current = current->next)
    {
        printf("%s\n", current->token);
    }

    // Free the memory allocated for the tokens in the list
    // for (current = list; current; current = current->next)
    // {
    //     free(current->token);
    //     free(current);
    // }




}
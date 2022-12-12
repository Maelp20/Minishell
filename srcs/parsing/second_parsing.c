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
    int i = 0;
    int token_start = 0;
    int token_length = 0;
    int prev_was_delimiter = 0;

    while (str[i])
    {
        // Check if the current character is one of the delimiters
        if (str[i] == '|' || str[i] == '>' || str[i] == '<')
        {
            // If the current token is not empty and the previous token was not a delimiter, add it to the list
			printf("str[%d] = %c\n",i, str[i]);
            if (token_length > 0 && !prev_was_delimiter)
            {
                if (head)
                {
                    current->next = malloc(sizeof(t_tok));
                    current = current->next;
                }
                else
                {
                    head = current = malloc(sizeof(t_tok));
                }

                // Copy the current token to the new t_tok structure
                current->token = malloc(token_length + 1);
                memcpy(current->token, str + token_start, token_length);
                current->token[token_length] = '\0';
                current->next = NULL;

                // Reset the token start and length for the next token
                token_start = i + 1;
                token_length = 0;
            }
            // Create a new token for the delimiter
         else
			{
				// Check if the current token is not empty
				if (token_length > 0)
				{
					if (head)
					{
						current->next = malloc(sizeof(t_tok));
						current = current->next;
					}
					else
					{
						head = current = malloc(sizeof(t_tok));
					}
					current->token = malloc(2);
					current->token[0] = str[i];
					current->token[1] = '\0';
					current->next = NULL;
				}
				prev_was_delimiter = 1;
			}
        }
        else
        {
            // If the current character is not a delimiter, increment the length of the current token
            token_length++;
            prev_was_delimiter = 0;
        }
        i++;
    }
    // Add the final token to the list if it is not empty and the previous token was not a delimiter
    if (token_length > 0 && !prev_was_delimiter)
    {
        if (head)
        {
            current->next = malloc(sizeof(t_tok));
            current = current->next;
        }
        else
        {
            head = current = malloc(sizeof(t_tok));
        }
        current->token = malloc(token_length + 1);
		memcpy(current->token, str + token_start, token_length);
		current->token[token_length] = '\0';
		current->next = NULL;
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
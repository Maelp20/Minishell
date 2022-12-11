#include "../../inc/exec.h"
//#include "exec.h"

// int	is_to_split(char c)
// {
// 	if ( c == '|' || c == '>' || c == '<')
// 		return (1);
// 	return (0);
// }

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


// // Function to split a string into tokens based on a specified delimiter
// char *ft_strtok(char *str, const char *delim)
// {
//     static char *saved_str;

// 	saved_str = NULL; // Static variable to save the string between calls
//     // Check if a new string was passed as the first argument
//     if (str != NULL)
//         saved_str = str;
//     else if (saved_str == NULL)
//         return NULL;
//     // Skip leading delimiters
//     char *current = saved_str;
//     while (*current != '\0' && ft_strchr(delim, *current) != NULL)
//         current++;
//     // If there are no more non-delimiter characters, return NULL
//     if (*current == '\0')
//         return NULL;
//     // Save the current position of the string and find the next delimiter
//     char *start = current;
//     while (*current != '\0' && ft_strchr(delim, *current) == NULL)
//         current++;
//     // If there are no more delimiters, set the saved pointer to NULL
//     if (*current == '\0')
//         saved_str = NULL;
//     else
//     {
//         // Otherwise, split the string at the delimiter and save the rest of the string
//         *current = '\0';
//         saved_str = current + 1;
//     }
//     return start;
// }


// // Function to split a string into tokens and store them in a linked list
// t_tok *split_string(const char *str)
// {
//     // Create an empty linked list to store the tokens
//     t_tok *list = NULL;
//     t_tok *current = NULL;

//     // Make a copy of the input string so we can modify it
//     char *copy = ft_strdup(str);
//     char *token = ft_strtok(copy, DELIMITERS); // Get the first token

//     // Continue splitting the string until there are no more tokens
//     while (token != NULL)
//     {
//         // Allocate memory for the new token
//         t_tok *new_token = (t_tok*)malloc(sizeof(t_tok));
//         new_token->token = ft_strdup(token); // Copy the token string
//         new_token->next = NULL; // Initialize the next pointer

//         // Add the token to the linked list
//         if (list == NULL)
//         {
//             // If the list is empty, set the new token as the first element
//             list = new_token;
//         }
//         else
//         {
//             // Otherwise, add the new token to the end of the list
//             current->next = new_token;
//         }

//         // Update the current pointer to the last token in the list
//         current = new_token;

//         // Get the next token
//         token = ft_strtok(NULL, DELIMITERS);
//     }

//     // Free the memory used for the copy of the input string
//     free(copy);

//     // Return the linked list of tokens
//     return list;
// }


//#define DELIMITERS "|><<>>" // Delimiters to split on

// Function to split a string into tokens based on the specified delimiters
// and include the delimiters in the resulting tokens
char *split_string(char *str)
{
    char *start = str; // Start of the current token
    char *current = str; // Current position in the string

    // Loop until the end of the string
    while (*current != '\0')
    {
        // Check if the current character is a delimiter
        if (strchr(DELIMITERS, *current) != NULL)
        {
            // If so, split the string at this point and save the rest of the string
            *current = '\0';
            str = current + 1;

            // Print the current token, including the delimiter
            printf("%s\n", start);

            // Update the start pointer to the next character after the delimiter
            start = str;
        }

        // Move to the next character in the string
        current++;
    }

    // Print the last token, if there is one
    if (start != current)
    {
        printf("%s\n", start);
    }

    // Return the rest of the string after the last delimiter
    return str;
}

int main(void)
{
    // Split the string on the delimiters and print each token
    char *str = "|J>>e>jesuis<<lol>";
    while (*str != '\0')
    {
        str = split_string(str);
    }
    return 0;
}


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
// 				//tmp = split_string((*lst)->token);
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
// 	 	printf("clean - %s\n", (*lst)->token);
// 	 	*lst = (*lst)->next;
// 	}
// }
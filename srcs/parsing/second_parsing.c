#include "exec.h"


void print_tok_list(t_tok *list)
{
    t_tok *current = list;
    while (current)
    {
        printf("%s\n", current->token);
        current = current->next;
    }
}

// int	is_separator(char c1, char c2)
// {
// 	if(c2 && ((c1 == '>'  && c2 == '>') || (c1 == '<' && c2 == '<')))
// 		return (2);
// 	if (c1 == '>' || c1 == '<' || c1 == '|')
// 		return (1);
// 	return (0);
// }

// char *split_char(char *token)
// {
//     char *splitted;
//     int i;

//     if (*token == '\0')
//         return "";  // Return an empty string if the input string is empty

//     i = 0;
//     if (is_separator(*token, *token + 1) == 2)
//         i = 2;
//     else if (is_separator(*token, *token + 1) == 1)
//         i = 1;
//     else
//     {
//         while (*token + i && !is_separator(*token + i, *token + i + 1))
//             i++;
//     }
//     splitted = malloc(sizeof(char) * (i + 1));
//     if (is_separator(*token, *token + 1) == 2)
//     {
//         while (i < 2)
//         {
//             splitted[i] = *token;
//             token++;
//             i++;
//         }
//     }
//     else if (is_separator(*token, *token + 1) == 1)
//     {
//         splitted[0] = *token;
//         token++;
//         i++;
//     }
//     else
//     {
//         i = 0;
//         while (*token + i && !is_separator(*token + i, *token + i + 1))
//         {
//             splitted[i] = *token;
//             token++;
//             i++;
//         }
//     }
//     splitted[i] = '\0';
//     return splitted;
// }


// void t_tok_append(t_tok **lst, t_tok *new)
// {
//     t_tok *curr;

//     if (*lst == NULL)
//     {
//         *lst = new;
//         return;
//     }

//     curr = *lst;
//     while (curr->next != NULL)
//         curr = curr->next;
//     curr->next = new;
// }


// void clean_token(t_tok **lst)
// {
//     while (*lst)
//     {
//         while (*((*lst)->token))
//         {
//             t_tok_append(lst, lstnew_token(split_char((*lst)->token)));
//         }
//         *lst = (*lst)->next;
//     }
// }

char *split_char(char *token)
{
	char *splitted;
	int i;

	i = 0;
	if (is_separator(*token, *token + 1) == 2)
		i = 2;
	else if (is_separator(*token, *token + 1) == 1)
		i = 1;
	else
	{
		while (*token + i && !is_separator(*token + i, *token + i + 1))
			i++;
	}
	splitted = malloc(sizeof(char) * (i + 1));
	if (is_separator(*token, *token + 1) == 2)
	{
		while (i < 2)
		{
			splitted[i] = *token;
			token++;
			i++;
		}
	}
	else if (is_separator(*token, *token + 1) == 1)
	{
		splitted[0] = *token;
		token++;
		i++;
	}
	else
	{
		i = 0;
		while (*token + i && !is_separator(*token + i, *token + i + 1))
		{
			splitted[i] = *token;
			token++;
			i++;
		}
	}
	splitted[i] = '\0';
	printf("splitted = %s\n", splitted);
	printf("token = %s\n", token);
	printf("test\n");
	return (splitted);
}


void	clean_token(t_tok **lst)
{
	while (*lst)
	{
		while(*((*lst)->token))
		{
			(*lst)->next = lstnew_token(split_char((*lst)->token));
			printf("clean token - token = %s\n", (*lst)->token);
		}
		*lst = (*lst)->next;
	}
}
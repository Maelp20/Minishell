#include "exec.h"

void add_to_list(t_tok **list, t_tok **current, t_tok *token)
{
	if (*current)
	{
		(*current)->next = token;
		*current = (*current)->next;
	}
	else
	{
		*list = token;
		*current = token;
	}
}

t_tok *split_string(const char *str, t_tok *list, t_tok *current )
{
  // Create a linked list to store the tokens
  t_tok	*token;
  // Create a temporary buffer to hold the current token
  char buf[strlen(str) + 1];
  int buf_pos = 0;
  // Loop through the input string
  size_t i = 0;
  while ( i < strlen(str))
  {
      // Check if the current character is a separator
    if (str[i] == '>' || str[i] == '<' || str[i] == '|' || (i < strlen(str) - 1 && str[i] == str[i + 1]))
    {
		// Add the separator as a token
		// Add the current token to the list
		buf[buf_pos] = '\0';
		token = lstnew_token(buf);
		add_to_list(&list, &current, token);
		// if (current)
		// {
		// 	current->next = token;
		// 	current = current->next;
		// }
		// else
		// {
		// 	list = token;
		// 	current = token;
		// }
		//Clear the buffer
		buf_pos = 0;
		// Create a new token for the separator
		t_tok *separator = malloc(sizeof(t_tok));
		separator->token = malloc(3);
		if (i < strlen(str) - 1 && str[i] == str[i + 1])
		{
			// Handle double separators
			separator->token[0] = str[i];
			separator->token[1] = str[i];
			separator->token[2] = '\0';
			i++; // Skip the next character
		}
		else
		{
			// Handle single separators
			separator->token[0] = str[i];
			separator->token[1] = '\0';
		}
		separator->next = NULL;
		// Add the separator to the list
		add_to_list(&list, &current, separator);
		// if (current)
		// {
		// 	current->next = separator;
		// 	current = current->next;
		// }
		// else
		// {
		// 	list = separator;
		// 	current = separator;
		// }
	}
	else
	{
		// Add the character to the current token buffer
		buf[buf_pos] = str[i];
		buf_pos++;
	}
 	i++;
	}
// Add the last token to the list
		if (buf_pos > 0) 
		{ // <-- Add this check
    		buf[buf_pos] = '\0';
    		t_tok *token = malloc(sizeof(t_tok));
    		token->token = strdup(buf);
    		token->next = NULL;
    		if (current)
        		current->next = token;
			else
        		list = token;
		}
	return list;
}


void	clean_token_lst(t_tok **lst)
{
	(void)lst;
	t_tok *list = NULL;
  	t_tok *current = NULL;
    // Split the string "|J>>e>jesuis<<lol>" into tokens
    t_tok *bis = split_string("|J>>e>jesuis|d>>lol>",list,current  );

    // Allocate memory for the current token in the list
    t_tok *truc = malloc(sizeof(t_tok));

    // Print the tokens in the list
    for (truc = bis; truc; truc = truc->next)
    {
        printf("%s\n", truc->token);
    }

    // Free the memory allocated for the tokens in the list
    // for (current = list; current; current = current->next)
    // {
    //     free(current->token);
    //     free(current);
    // 
}
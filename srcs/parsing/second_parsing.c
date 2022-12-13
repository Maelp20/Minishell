#include "exec.h"

t_tok *split_string(const char *str)
{
  // Create a linked list to store the tokens
  t_tok *list = NULL;
  t_tok *current = NULL;

  // Create a temporary buffer to hold the current token
  char buf[strlen(str) + 1];
  int buf_pos = 0;

  // Loop through the input string
  size_t i = 0;
  while ( i < strlen(str))
  {
    char c = str[i];

    // Check if the current character is a separator
    if (c == '>' || c == '<' || c == '|' || (i < strlen(str) - 1 && str[i] == str[i + 1]))
    {
		// Add the separator as a token
		// Add the current token to the list
		buf[buf_pos] = '\0';
		t_tok *token = malloc(sizeof(t_tok));
		token->token = strdup(buf);
		token->next = NULL;
		if (current)
		{
			current->next = token;
			current = current->next;
		}
		else
		{
			list = token;
			current = token;
		}
		// Clear the buffer
		buf_pos = 0;
		// Create a new token for the separator
		t_tok *separator = malloc(sizeof(t_tok));
		separator->token = malloc(3);
		if (i < strlen(str) - 1 && str[i] == str[i + 1])
		{
			// Handle double separators
			separator->token[0] = c;
			separator->token[1] = c;
			separator->token[2] = '\0';
			i++; // Skip the next character
		}
		else
		{
			// Handle single separators
			separator->token[0] = c;
			separator->token[1] = '\0';
		}
		separator->next = NULL;
		// Add the separator to the list
		if (current)
		{
			current->next = separator;
			current = current->next;
		}
		else
		{
			list = separator;
			current = separator;
		}
	}
	else
	{
		// Add the character to the current token buffer
		buf[buf_pos] = c;
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
	
    // Split the string "|J>>e>jesuis<<lol>" into tokens
    t_tok *list = split_string("|J>>e>jesuis|d>>lol>");

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
    // 
}
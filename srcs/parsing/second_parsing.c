#include "exec.h"


void printlist(t_tok **lst)
{
	while (*lst)
	{
		printf("%s\n",(*lst)->token);
		*lst = (*lst)->next;
	}
}

int is_separator(char *token)
{
	int i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '|' || token[i] == '<' || token[i] == '>')
			return(1);
		i++;
	}
	return (0);
}

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

size_t add_separator(const char *str, size_t i, t_tok **list, t_tok **current)
{
	t_tok *separator;

	separator = malloc(sizeof(t_tok));
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
	add_to_list(list, current, separator);
	return (i);
}

void create_token(t_tok **list, t_tok *current, char *buf, int buf_pos)
{
  t_tok *token;

  token = malloc(sizeof(t_tok));
  if (buf_pos > 0)
  {
    buf[buf_pos] = '\0';
    token->token = strdup(buf);
    token->next = NULL;
    if (current)
      current->next = token;
    else
      *list = token;
    // Update the current pointer to point to the newly-created token
    current = token;
  }
}


t_tok *split_string(const char *str, t_tok *list, t_tok *current )
{
  // Check if the input string is empty
	if (strlen(str) == 0)
	{
		// Return a null pointer if the input string is empty
		return NULL;
	}
	// Create a linked list to store the tokens
	t_tok	*token;
	// Create a temporary buffer to hold the current token
	char buf[strlen(str) + 1];
	int buf_pos;
	size_t	i;

	buf_pos = 0;
	i = 0;
	// Loop through the input string
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
      // Clear the buffer
      buf_pos = 0;
      // Create a new token for the separator
      i = add_separator(str,i, &list, &current);
    }
    else
    {
      // Add the character to the current token buffer
      buf[buf_pos] = str[i];
      buf_pos++;
    }
    // Increment the loop variable
    i++;
  }
  // Add the last token to the list
  create_token(&list, current, buf, buf_pos);

  // Return the updated linked list
  return list;
}


// void insert_linked_list(t_tok* pos, t_tok* list) {
//   if (pos == NULL || list == NULL) return; // check for invalid input

//   // find the last node in the inserted linked list
//   t_tok* last = list;
//   while (last->next != NULL) {
//     last = list->next;
//   }

//   // insert the linked list after the given position and remove the
//   // original node by setting the next pointer of the given position
//   // to point to the first node of the inserted list and freeing
//   // the memory of the original node
//   t_tok* next = pos->next;
//   pos->next = list;
//   last->next = next;
// 	printlist(&list);
//   // free the memory of the original node
// }


void	clean_token_lst(t_tok **lst)
{
	t_tok *list = NULL;
  	t_tok *current = NULL;
	t_tok *tmp;
	t_tok *head;

	head = *lst;
    while (*lst)
	{
		if (is_separator((*lst)->token))
		{	
			tmp = split_string((*lst)->token,list,current);
			//printlist(&tmp);
			//printf("%s\n", (*lst)->token);
			//insert_linked_list(*lst, tmp);
		}
		*lst = (*lst)->next;
	}
	*lst = head;
}




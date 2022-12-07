#include "exec.h"


int	is_separator(char c)
{
	return (c == '|' || c == '>' || c == '<'  );
}
// void	split_operator(t_tok **tok_lst, t_data **lst)
// {
// 	size_t	firstlen;
// 	size_t	secondlen;
// 	size_t	sizeofoutput;
// 	int i;
// 	char *equalpos;
// 	char **output;

// 	while(tok_lst)
// 	{
// 		//calcul the size of the output
// 		sizeofoutput = 0;
// 		i = -1;
// 		while((*tok_lst)->token[++i])
// 		{
// 			if (is_separator((*tok_lst)->token[++i]))
// 				sizeofoutput++;
// 		}
// 		output = malloc(sizeof(char *) * (sizeofoutput + 1));


		
// 		(*tok_lst) = (*tok_lst)->next;
// 	}
	
// 	//free() tok_lst;
// }


void print_t_data_list_args(t_data *data)
{
	while (data)
	{
		int i;
		for (i = 0; data->args[i]; i++)
		printf("arg[%d]: %s\n", i, data->args[i]);
		data = data->next;
	}
}

size_t strnlen(const char *s, size_t maxlen)
{
	size_t len;
	for (len = 0; len < maxlen && s[len] != '\0'; len++);
	return len;
}

char *strndup(const char *s, size_t n)
{
	size_t len = strnlen(s, n);
	char *result = malloc(len + 1);
	if (result == NULL)
		return NULL;

	memcpy(result, s, len);
	result[len] = '\0';
	return result;
}

void	split_operator(t_tok **tok_lst, t_data **lst)
{
	// Initialize variables
	size_t sizeofoutput = 0;
	char **output = NULL;
	t_data *new_data = NULL;
	int i;

	// Loop through the linked list
	while (*tok_lst)
	{
		// Calculate the size of the output array
		sizeofoutput = 0;
		for (i = 0; (*tok_lst)->token[i]; i++)
		{
			if (is_separator((*tok_lst)->token[i]))
				sizeofoutput++;
		}

		// Allocate memory for the output array and initialize it to zero
		output = malloc(sizeof(char *) * (sizeofoutput + 1));
		memset(output, 0, sizeof(char *) * (sizeofoutput + 1));

		// Split the tokens into the output array
		sizeofoutput = 0;
		for (i = 0; (*tok_lst)->token[i]; i++)
		{
			if (is_separator((*tok_lst)->token[i]))
			{
				// Add the token to the output array
				output[sizeofoutput] = strndup((*tok_lst)->token, i);

				// Check if the strndup function failed to allocate memory
				if (output[sizeofoutput] == NULL)
				{
					// Free the memory used by the output array
					for (i = 0; i < (int)sizeofoutput; i++)
					{
						if (output[i] != NULL)
							free(output[i]);
					}
					free(output);

					// Return an error
					return;
				}

				// Advance to the next token
				(*tok_lst) = (*tok_lst)->next;

				// Increment the size of the output array
				sizeofoutput++;
			}
		}

		// Add the last token to the output array
		output[sizeofoutput] = strndup((*tok_lst)->token, i);

		// Check if the strndup function failed to allocate memory
		if (output[sizeofoutput] == NULL)
		{
			// Free the memory used by the output array
			for (i = 0; i < (int)sizeofoutput; i++)
			{
				if (output[i] != NULL)
					free(output[i]);
			}
			free(output);

			// Return an error
			return;
		}

		// Create a new t_data element and store the output array
		new_data = malloc(sizeof(t_data));
		new_data->args = output;

		// Add the new t_data element to the linked list
		if (*lst == NULL)
		{
			// If the list is empty, set the new element as the head of the list
			*lst = new_data;
		}
		else
		{
			// If the list is not empty, find the last element and append the new element to it
			t_data *curr = *lst;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = new_data;
		}

		// Advance to the next token
		(*tok_lst) = (*tok_lst)->next;
	}

	// Free the memory used by the token list
	free(*tok_lst);
}

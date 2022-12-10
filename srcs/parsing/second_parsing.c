#include "exec.h"

int	is_to_split(char c)
{
	if ( c == '|' || c == '>' || c == '<')
		return (1);
}


int	split_pipe_and_chev(t_tok *lst, int i, t_tok **lst)
{
	
}
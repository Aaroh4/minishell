#include "./includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigint_handler(int signum) {
	signum = 0;
    ft_printf("Caught SIGINT. Exiting...\n");
    return ;
}

int	main(void)
{
	signal(SIGINT, sigint_handler);
	char	*input;
	while((input = readline("minishell > ")) != NULL)
	{
		if (*input == 'a')
			break;
	}
}

#include "./includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>


void ft_signal_handle(int signal_num) {
   // printf("Received signal: %d\n", signal_num);
   int	i = 0;
   if (i == signal_num)
	i = 1;
}

void enableRawMode() {
	struct termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int	main(void)
{
	char	*input;
	char	**arr;
	int		i;
	enableRawMode();

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_handle);

	while (1)
	{
		input = readline("minishell > ");
		if (!ft_strncmp(input, "break", 5) || input == NULL)
			return (0);
		arr = ft_split(input, "<>");
		i = 0;
		while (arr[i] != '\0')
		{
			printf("%s\n", arr[i]);
			i++;
		}
	}
}

#include "./includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <fcntl.h>

void enableRawMode() {
	struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1)
		perror("tcgetattr");
    term.c_lflag &= ~(ICANON | ECHOCTL);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
}

void	ft_handler(int signum)
{
	signum = 1;
	write(1, "\nminishell > ", 13);
}

int	main(void)
{
	char	*input;
	char	**arr;
	enableRawMode();
	//int		i;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);

	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd error");
	while (1)
	{
		input = readline("minishell > ");
		if (input == NULL || !ft_strncmp(input, "exit", 5))
			exit_builtin();
		if (!ft_strncmp(input, "pwd", 5))
			pwd_builtin();
		arr = ft_split(input, " ");
		if (arr[0] != '\0' && !ft_strncmp(arr[0], "cd", 2))
			cd_builtin(cwd, arr);
		//i = 0;
		//while (arr[i] != '\0')
		//{
		//	printf("%s\n", arr[i]);
		//	i++;
		//}
	}
}

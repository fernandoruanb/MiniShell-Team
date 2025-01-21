#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*display_prompt(void)
{
	return ("User: ");
}

void	get_input(void)
{
	char	*input;

	while (1)
	{
		input = readline(display_prompt());
		printf("O seu input foi: %s\n", input);
	}
}

int	main(void)
{
	get_input();
	return (0);
}

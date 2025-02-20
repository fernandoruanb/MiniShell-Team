
#include <unistd.h>
#include <sys/wait.h>


int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;

	if (argc == 1)
		return (0);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		execve("/usr/bin/echo", &argv[1], envp);
	waitpid(pid, NULL, 0);
	return (0);
}

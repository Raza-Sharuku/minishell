#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig;

static void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
	}
}

int	set_sigint(char *a)
{
	struct sigaction	sigstruct;

	sigemptyset(&sigstruct.sa_mask);
	sigstruct.sa_handler = handle_sigint;
	sigstruct.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigstruct, NULL) == -1)
		return (-1);
	sigstruct.sa_handler = SIG_IGN;
	sigstruct.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sigstruct, NULL) == -1)
		return (-1);
	if(g_sig==SIGINT)
	*a='b';
	return (0);
}

int	main(void)
{
	char a;
	a='a';
	set_sigint(&a);
	while(g_sig!=SIGINT)
	{

	}
	write(1,&a,1);
	write(1,"\n",1);
	return(0);
}

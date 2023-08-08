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

int	main(void)
{
	int tmp;
	tmp=dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	write(tmp,"hello\n",6);
	dup2(tmp,STDOUT_FILENO);
	write(1,"hello2\n",7);
	write(tmp,"hello3\n",7);	
	return(0);
}



#include "my_signal.h"

err_t sig_init()
{
	struct sigaction send_sig;
	send_sig.sa_flags = SA_SIGINFO;
	send_sig.sa_sigaction = &signal_handler;
	if(sigaction(SIGINT, &send_sig, NULL))
	{
		perror("sigaction()\n");
		return errno;
	}
}


void signal_handler(int signo, siginfo_t *info, void *extra)
{
	if(signo == 2)
	{
		printf("Terminating due to signal number = %d.\n", signo);
		queues_close();
		queues_unlink();
		
		//The below command should come after printing terminating in the text file.
		exit(EXIT_SUCCESS);
	}
}

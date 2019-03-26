
#include "my_signal.h"

err_t sig_init()
{
	struct sigaction send_sig;
	send_sig.sa_flags = SA_SIGINFO;
	send_sig.sa_sigaction = &signal_handler;
	if(sigaction(SIGINT, &send_sig, NULL))
	{
		error_log("ERROR: sigaction(); in sig_init() function");
	}
}


void signal_handler(int signo, siginfo_t *info, void *extra)
{
	if(signo == 2)
	{
		queues_close();
		queues_unlink();

		if (pthread_mutex_destroy(&mutex_a))
		{
			error_log("ERROR: pthread_mutex_destroy(mutex_a); cannot destroy mutex_a");
		}

		if (pthread_mutex_destroy(&mutex_error))
		{
			error_log("ERROR: pthread_mutex_destroy(mutex_error); cannot destroy mutex_error");
		}

		printf("\nTerminating due to signal number = %d.\n", signo);
		//The below command should come after printing terminating in the text file.
		exit(EXIT_SUCCESS);
	}
}

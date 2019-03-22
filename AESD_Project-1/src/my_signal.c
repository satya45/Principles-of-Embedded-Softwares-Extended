
#include "my_signal.h"

void sig_init()
{
	struct sigaction send_sig;
	send_sig.sa_flags = SA_SIGINFO;
	send_sig.sa_sigaction = &signal_handler;
	if(sigaction(SIGINT, &send_sig, NULL))
	{
		perror("sigaction()\n");
		exit(EXIT_FAILURE);
	}
}


void signal_handler(int signo, siginfo_t *info, void *extra)
{
	if(signo == 2)
	{
		printf("Terminating.. %d", signo);
		mq_close(heartbeat_mq);
		mq_close(log_mq);
		mq_close(sock_mq);
		mq_close(log_sock_mq);
		exit(1);
	}
}

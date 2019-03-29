
/**
 * @file my_signal.c
 * @author Siddhant Jajoo and Satya Mehta
 * @brief This file consists of all the functions related to signals.
 * @version 0.1
 * @date 2019-03-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */


#include "my_signal.h"

/**
 * @brief - This function initializes the signal handling capabilities.
 * 
 * @return err_t 
 */
err_t sig_init()
{
	struct sigaction send_sig;
	send_sig.sa_flags = SA_SIGINFO;
	send_sig.sa_sigaction = &signal_handler;
	if (sigaction(SIGINT, &send_sig, NULL))
	{
		error_log("ERROR: sigaction(); in sig_init() function");
	}
	if (sigaction(SIGPIPE, &send_sig, NULL))
	{
		error_log("ERROR: sigaction(); in sig_init() SIGPIPE function");
	}
}

/**
 * @brief - This function is the signal handler. On a signal interruption, the execution is transferred
 * 			to this function.
 * 
 * @param signo -  Gives the signal number due to which interruption has occurred. 
 * @param info 
 * @param extra 
 */

void signal_handler(int signo, siginfo_t *info, void *extra)
{
	if (signo == 2)
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

		//delete timers

		main_exit = 1;
		printf("\nTerminating due to signal number = %d.\n", signo);
		//The below command should come after printing terminating in the text file.
		exit(EXIT_SUCCESS);
	}
	if (signo == 13)
	{
		printf("Sigpipe rcvd\n");
	}
}

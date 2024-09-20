/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:21:30 by randrade          #+#    #+#             */
/*   Updated: 2024/09/16 14:34:53 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <signal.h>
#include <stdlib.h>

void signal_handler(int signum)
{
  printf("Received SIGINT!\n", signum);
  exit(0);
}

int main()
{
  // Set the signal handler for the SIGINT and SIGTERM signals
  // to the signal_handler function

	pid_t pid;
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);
  pid = getpid();

  while (1) 
  {
	 printf("ID: %d\n", pid); 
	  sleep(3);
  }

  return 0;
}
//int	main(int argc, char *argv[])
//{
//  	pid_t pid;
//
//	pid = getpid();
//	printf("The process ID is %d\n", pid);
//
//	return (0);
//}

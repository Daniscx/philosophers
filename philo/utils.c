/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:03:30 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/21 19:56:38 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *nb)
{
	int	i;
	int	nba;
	int	sing;

	i = 0;
	sing = 1;
	nba = 0;
	if (nb[i] == '-')
	{
		sing = -1;
		i++;
	}
	else if (nb[i] == '+')
		i++;
	while (nb[i])
	{
		if (nb[i] > '9' || nb[i] < '0')
			return (0);
		nba = nb[i] - '0' + (nba * 10);
		i++;
	}
	return (nba * sing);
}

void	error_manager(char *error)
{
	printf("%s\n", error);
	exit(1);
}

long	get_timestamp_in_ms(struct timeval start, struct timeval current)
{
	return (((current.tv_sec - start.tv_sec) * 1000L) + ((current.tv_usec
				- start.tv_usec) / 1000L));
}

int	action_protection(t_philo *pn, char *message)
{
	int	i;

	i = 0;
	pthread_mutex_lock(pn->status_door);
	i = action_checker_for_actions(pn, message);
	pthread_mutex_unlock(pn->status_door);
	if (i == 1)
		return (1);
	return (0);
}
void usleep_better(t_philo * philo,long int time)
{
	struct timeval actual_time;
	long time_passed;
	gettimeofday(&actual_time, NULL);
	time_passed = get_timestamp_in_ms(philo->since_eat,actual_time);
	if(time_passed + time > philo->time.time_to_die * 1000L)
		usleep(philo->time.time_to_die * 1000L - time_passed);
	else
		usleep(time);
}


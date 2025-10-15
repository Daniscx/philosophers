/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:42:37 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/15 18:48:40 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "unistd.h"

static int	forks_everyone(int *table, int phnb, t_philo *philo,
				struct timeval since_eat);

int	table(int phnb, t_philo *philo, struct timeval since_eat)
{
	static int	*table = NULL;
	static int	max = 0;
	int			i;

	i = 0;
	if (!table)
	{
		table = malloc(phnb * sizeof(int));
		max = phnb;
		while (phnb != 0)
		{
			table[phnb - 1] = 0;
			phnb--;
		}
		return (0);
	}
	if (phnb == 0)
		return (free(table), 0);
	if (phnb == max)
		return (fork_for_max(table, max - 1, philo, since_eat));
	else
		return (forks_everyone(table, phnb, philo, since_eat));
}

static int	forks_everyone(int *table, int phnb, t_philo *philo,
		struct timeval since_eat)
{
	if (phnb % 2 == 0)
		return (eating_for_pair(table, phnb, philo, since_eat));
	else
		return (eating_for_unpair(table, phnb, philo, since_eat));
}

int	taking_fork(int *table, int phb, struct timeval since_eat,
		t_philo *philo)
{
	int	i;

	i = 0;
	if (table[phb] == 0)
	{
		i = action_protection(since_eat, philo, "has taken a fork");
		return (i);
	}
	return (2);
}

void	release_fork(int *table, int phnb)
{
	if (table[phnb] == 1)
		table[phnb] = 0;
}

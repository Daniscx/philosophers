/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pilosophers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:54:25 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/16 16:43:31 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	forks(t_philo *philo, struct timeval time_since_eat);
void	position_fork(int pnb, int *left, int *right, int max);
t_ttime	init_time(char **argv);
void	destroy_philo(t_philo *philo);

int	main(int args, char **argv)
{
	int		pnb;
	t_ttime	time;

	if (args != 5 && args != 6)
		error_manager(("Check the args amount of args please"));
	pnb = ft_atoi(argv[1]);
	if (pnb <= 0)
		error_manager(("It have to be for least 1 philosopher "));
	time = init_time(argv);
	table(pnb, NULL);
	init_the_threads(time, pnb);
	return (0);
}

t_ttime	init_time(char **argv)
{
	t_ttime	time;

	time.time_to_die = ft_atoi(argv[2]);
	time.time_sleep = ft_atoi(argv[4]);
	time.time_to_eat = ft_atoi(argv[3]);
	if (argv[5])
	{
		time.times_to_eat = ft_atoi(argv[5]);
		if (time.times_to_eat < 0)
			error_manager("Check the arguments please");
	}
	else
		time.times_to_eat = -1;
	if (time.time_sleep <= 0 || time.time_to_die <= 0 || time.time_to_eat <= 0)
		error_manager("Check the arguments please");
	return (time);
}

void	*philos(void *pn)
{
	t_philo			*philo;

	philo = (t_philo *)pn;
	gettimeofday(&(philo->since_Eat), NULL);
	only_one_philo_routine(philo, philo->since_Eat);
	while (1)
	{
		while (table(philo->nbph, philo) != 0)
		{
			if (action_protection(philo->since_Eat, philo, NULL) == 1)
				destroy_philo(philo);
		}
		if (action_protection(philo->since_Eat, philo, "is thinking") == 1)
			destroy_philo(philo);
		if (action_protection(philo->since_Eat, philo, "is sleeping") == 1)
			destroy_philo(philo);
		usleep(philo->time.time_sleep * 1000L);
	}
}

void	destroy_philo(t_philo *philo)
{
	free(philo);
	pthread_exit(0);
}

t_philo	*init_philos(t_ttime asignation, int nbph)
{
	t_philo	*aux;

	aux = NULL;
	aux = malloc(1 * sizeof(t_philo));
	aux->nbph = nbph;
	aux->time = asignation;
	aux->checker = NULL;
	aux->left_fork = NULL;
	aux->right_fork = NULL;
	aux->status_door = NULL;
	return (aux);
}

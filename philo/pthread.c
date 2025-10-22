/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:57:40 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/21 18:50:12 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "pthread_use.h"

static void	new_pthread(t_list *pthread_list, t_philo *philo);
static void	philo_assignation(t_philo *philo, t_checker *checker,
				pthread_mutex_t *status_door);

static void	fork_assignation(t_philo *first_one, t_philo *philo)
{
	if (philo)
		first_one->right_fork = philo->left_fork;
}

static void	element_destroyer(t_checker *checker, pthread_mutex_t *status_door)
{
	pthread_mutex_destroy(status_door);
	free(status_door);
	free(checker);
}

void	init_the_threads(t_ttime time, int pnb)
{
	t_checker		*checker;
	t_philo			*philo;
	t_list			*pthreads_list;
	pthread_mutex_t	*status_door;
	t_philo			*first_one;

	philo = NULL;
	checker = init_checker(pnb);
	pthreads_list = init_list(pnb);
	status_door = init_mutext();
	first_one = init_philos(time, pnb);
	philo_assignation(first_one, checker, status_door);
	pnb--;
	while (pnb != 0)
	{
		philo = init_philos(time, pnb);
		philo_assignation(philo, checker, status_door);
		new_pthread(pthreads_list, philo);
		pnb--;
	}
	fork_assignation(first_one, philo);
	new_pthread(pthreads_list, first_one);
	dead_checker(pthreads_list);
	list_destroyer(pthreads_list);
	element_destroyer(checker, status_door);
}

static void	new_pthread(t_list *pthread_list, t_philo *philo)
{
	pthread_t	*new_thread_to_add_to_the_list;

	new_thread_to_add_to_the_list = malloc(sizeof(pthread_t));
	pthread_create(new_thread_to_add_to_the_list, NULL, philos, philo);
	add_element_to_list(pthread_list,
		create_new_node(new_thread_to_add_to_the_list, philo),
		philo->left_fork);
}

static void	philo_assignation(t_philo *philo, t_checker *checker,
		pthread_mutex_t *status_door)
{
	philo->checker = checker;
	philo->status_door = status_door;
	forks_creator(philo);
}

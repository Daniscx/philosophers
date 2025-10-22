/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:07:24 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/21 18:35:15 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H

# define LIST_H

# include "philosophers.h"
# include "pthread_use.h"

typedef struct philo_s t_philo;
typedef struct node_s
{
	pthread_t		*thread;
	t_philo			*philo;
	struct node_s	*next;
}					t_node;
typedef struct list_s
{
	t_node			*head;
	pthread_mutex_t	**array_of_mutex;
	size_t			size;

}					t_list;

t_list				*init_list(int size);
void				list_destroyer(t_list *list);
void				add_element_to_list(t_list *list, t_node *new_element,
						pthread_mutex_t *new_mutex);
t_node				*create_new_node(pthread_t *content, t_philo *philo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_use.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:07:32 by dmaestro          #+#    #+#             */
/*   Updated: 2025/10/11 21:08:50 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTHREAD_USE_H

# define PTHREAD_USE_H

# include "pthread.h"
# include "unistd.h"

typedef struct s_ttime	t_ttime;
pthread_mutex_t			*init_mutext(void);
void					init_the_threads(t_ttime time, int pnb);

#endif

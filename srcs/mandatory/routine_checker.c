/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:27:26 by dbislimi          #+#    #+#             */
/*   Updated: 2024/10/01 15:53:27 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	check_full(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->nb_of_philos)
	{
		pthread_mutex_lock(&table->check_full[i]);
		if (!table->philos[i].full)
		{
			pthread_mutex_unlock(&table->check_full[i]);
			return (false);
		}
		pthread_mutex_unlock(&table->check_full[i]);
	}
	return (true);
}

bool	check_dead(t_table *table)
{
	size_t	time;
	long	i;

	i = -1;
	while (++i < table->nb_of_philos)
	{
		time = get_current_time() - table->start_time;
		pthread_mutex_lock(&table->check_meals[i]);
		if ((size_t)table->time_to_die <= time - table->philos[i].last_meal)
		{
			pthread_mutex_lock(&table->check_dead);
			table->dead = 1;
			pthread_mutex_unlock(&table->check_dead);
			printf("%zu %d died\n", time, table->philos[i].id);
			pthread_mutex_unlock(&table->check_meals[i]);
			return (true);
		}
		pthread_mutex_unlock(&table->check_meals[i]);
	}
	return (false);
}

void	*routine_checker(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_full(table))
			return (NULL);
		if (check_dead(table))
			return (NULL);
	}
	return (NULL);
}

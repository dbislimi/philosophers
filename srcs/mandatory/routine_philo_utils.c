/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:49:07 by dbislimi          #+#    #+#             */
/*   Updated: 2024/10/01 14:49:59 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	return (philo->full);
}

void	increase_meal(t_philo *philo)
{
	if (++philo->nb_of_meals == philo->table->nbr_limit_meal)
	{
		pthread_mutex_lock(&philo->table->check_full[philo->id - 1]);
		philo->full = true;
		pthread_mutex_unlock(&philo->table->check_full[philo->id - 1]);
	}
}

void	wait_all_threads(t_table *table)
{
	pthread_mutex_lock(&table->ready);
	pthread_mutex_unlock(&table->ready);
}

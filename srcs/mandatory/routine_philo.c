/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:58:16 by dbislimi          #+#    #+#             */
/*   Updated: 2024/10/01 15:52:57 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	thinking(t_philo *philo)
{
	if (end_simulation(philo))
		return (1);
	printf("%zu %d is thinking\n",
		get_current_time() - philo->start, philo->id);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (end_simulation(philo))
		return (1);
	printf("%zu %d is sleeping\n",
		get_current_time() - philo->start, philo->id);
	ft_usleep(philo->table->time_to_sleep);
	return (0);
}

int	eating(t_philo *philo)
{
	long	time;

	if (end_simulation(philo))
		return (1);
	pthread_mutex_lock(philo->right);
	if (end_simulation(philo))
		return (1);
	printf("%zu %d has taken a fork\n",
		get_current_time() - philo->start, philo->id);
	if (philo->table->nb_of_philos == 1)
		return (1);
	pthread_mutex_lock(philo->left);
	if (end_simulation(philo))
		return (1);
	time = get_current_time() - philo->start;
	printf("%zu %d has taken a fork\n", time, philo->id);
	pthread_mutex_lock(&philo->table->check_meals[philo->id - 1]);
	philo->last_meal = time;
	pthread_mutex_unlock(&philo->table->check_meals[philo->id - 1]);
	printf("%zu %d is eating\n", time, philo->id);
	ft_usleep(philo->table->time_to_eat);
	increase_meal(philo);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	philo->start = philo->table->start_time;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!end_simulation(philo))
	{
		if (eating(philo) || sleeping(philo) || thinking(philo))
			break ;
	}
	return (NULL);
}

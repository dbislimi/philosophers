/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:56:04 by dbislimi          #+#    #+#             */
/*   Updated: 2024/10/01 16:05:19 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	destroy_mutexes(t_table *table)
{
	long	i;

	i = -1;
	if (table->forks)
	{
		while (++i < table->nb_of_philos)
			pthread_mutex_destroy(&table->forks[i]);
		free(table->forks);
	}
	i = -1;
	if (table->check_meals)
	{
		while (++i < table->nb_of_philos)
			pthread_mutex_destroy(&table->check_meals[i]);
		free(table->check_meals);
	}
	i = -1;
	if (table->check_full)
	{
		while (++i < table->nb_of_philos)
			pthread_mutex_destroy(&table->check_full[i]);
		free(table->check_full);
	}
	pthread_mutex_destroy(&table->check_dead);
	pthread_mutex_destroy(&table->ready);
}

bool	mutexes_init(t_table *table)
{
	long	i;

	pthread_mutex_init(&table->ready, NULL);
	pthread_mutex_init(&table->check_dead, NULL);
	i = -1;
	table->forks = malloc(sizeof(t_mtx) * table->nb_of_philos);
	if (!table->forks)
		return (1);
	while (++i < table->nb_of_philos)
		pthread_mutex_init(&table->forks[i], NULL);
	table->check_meals = malloc(sizeof(t_mtx) * table->nb_of_philos);
	if (!table->check_meals)
		return (1);
	i = -1;
	while (++i < table->nb_of_philos)
		pthread_mutex_init(&table->check_meals[i], NULL);
	table->check_full = malloc(sizeof(t_mtx) * table->nb_of_philos);
	if (!table->check_full)
		return (1);
	i = -1;
	while (++i < table->nb_of_philos)
		pthread_mutex_init(&table->check_full[i], NULL);
	return (0);
}

bool	philos_init(t_table *table)
{
	long	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->nb_of_philos);
	if (!table->philos)
		return (1);
	while (++i < table->nb_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = false;
		table->philos[i].right = &table->forks[i];
		table->philos[i].left = &table->forks[(i + 1) % table->nb_of_philos];
		table->philos[i].table = table;
	}
	return (0);
}

bool	thread_init(t_table *table)
{
	long	i;

	i = -1;
	if (table->nbr_limit_meal == 0)
		return (1);
	table->dead = 0;
	pthread_mutex_lock(&table->ready);
	table->all_threads_ready = false;
	while (++i < table->nb_of_philos)
	{
		table->philos[i].last_meal = 0;
		table->philos[i].nb_of_meals = 0;
		if (pthread_create(&table->philos[i].thread, NULL,
				&routine_philo, &table->philos[i]))
		{
			ft_free_philo(table, CREATE);
			return (1);
		}
	}
	table->start_time = get_current_time();
	table->all_threads_ready = true;
	pthread_mutex_unlock(&table->ready);
	pthread_create(&table->checker, NULL, &routine_checker, table);
	return (0);
}

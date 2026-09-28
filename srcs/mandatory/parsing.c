/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:37:05 by dbislimi          #+#    #+#             */
/*   Updated: 2024/10/01 15:19:30 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atol_philo(char *s)
{
	int		i;
	long	res;
	int		sign;
	int		size;

	size = 0;
	res = 0;
	sign = 1;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		++i;
	while (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign *= -1;
	if (sign == -1)
		return (-1);
	while (size <= 10 && (s[i] >= '0' && s[i] <= '9'))
	{
		res = res * 10 + (s[i] - '0');
		++size;
		++i;
	}
	if (res > INT_MAX || size > 10)
		return (-2);
	return (res);
}

int	parsing(t_table *table, char **av)
{
	table->nb_of_philos = ft_atol_philo(av[1]);
	if (table->nb_of_philos < 0)
		return (table->nb_of_philos);
	table->time_to_die = ft_atol_philo(av[2]);
	if (table->time_to_die < 0)
		return (table->time_to_die);
	table->time_to_eat = ft_atol_philo(av[3]);
	if (table->time_to_eat < 0)
		return (table->time_to_eat);
	table->time_to_sleep = ft_atol_philo(av[4]);
	if (table->time_to_sleep < 0)
		return (table->time_to_sleep);
	if (av[5])
	{
		table->nbr_limit_meal = ft_atol_philo(av[5]);
		if (table->nbr_limit_meal < 0)
			return (table->nbr_limit_meal);
	}
	else
		table->nbr_limit_meal = -1;
	return (0);
}

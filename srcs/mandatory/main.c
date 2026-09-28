/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:55:44 by dbislimi          #+#    #+#             */
/*   Updated: 2024/10/01 15:59:44 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	int		error;
	long	i;

	i = -1;
	if (ac < 5 || ac > 6)
		return (printf("%s%s%s\n", R, INPUT, RST));
	error = parsing(&table, av);
	if (error)
	{
		if (error == -1)
			return (printf("%s%s%s\n", R, NE, RST));
		return (printf("%s%s%s\n", R, INTMAX, RST));
	}
	if (mutexes_init(&table) || philos_init(&table) || thread_init(&table))
	{
		ft_free_philo(&table, MALLOC);
		return (1);
	}
	if (pthread_join(table.checker, NULL))
		ft_free_philo(&table, JOIN);
	while (++i < table.nb_of_philos)
		if (pthread_join(table.philos[i].thread, NULL))
			ft_free_philo(&table, JOIN);
	ft_free_philo(&table, NULL);
}

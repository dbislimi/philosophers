/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:56:08 by dbislimi          #+#    #+#             */
/*   Updated: 2024/10/01 15:59:44 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define G "\033[32m"
# define R "\033[1;31m"
# define RED "\033[31m"
# define RST "\033[0m"
# define NE "Error: unvalid inputs\n\033[0m \033[31m(negative number)"
# define INTMAX "Error: unvalid inputs\n\033[0m \033[31m(INT_MAX)"
# define INPUT "Error: wrong input.\n\033[32mCorrect is ./philo 5 800 200 200"
# define CREATE "Error: failed to create a thread.\n"
# define JOIN "Error: failed to join a thread.\n"
# define MALLOC "Error: failed to malloc something.\n"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	size_t		start;
	long		nb_of_meals;
	bool		full;
	size_t		last_meal;

	t_mtx		*left;
	t_mtx		*right;
	t_table		*table;
}	t_philo;

struct s_table
{
	long		nb_of_philos;
	long		time_to_eat;
	long		time_to_die;
	long		time_to_sleep;
	long		nbr_limit_meal;
	size_t		start_time;
	bool		all_threads_ready;
	bool		dead;

	pthread_t	checker;
	t_mtx		ready;
	t_mtx		*check_full;
	t_mtx		*check_meals;
	t_mtx		check_dead;
	t_philo		*philos;
	t_mtx		*forks;
};

void	ft_free_philo(t_table *table, char *msg);

int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

int		parsing(t_table *table, char **av);
bool	mutexes_init(t_table *table);
void	destroy_mutexes(t_table *table);
bool	philos_init(t_table *table);
bool	thread_init(t_table *table);

int		end_simulation(t_philo *philo);
void	increase_meal(t_philo *philo);
void	wait_all_threads(t_table *table);
void	*routine_philo(void *arg);
void	*routine_checker(void *arg);

#endif
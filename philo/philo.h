/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:02:39 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 13:18:29 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_parameters
{
	int				num_of_philos;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				times_to_eat;
	int				all_eat;
	int				someone_died;
	int				*fork;
	int				counter;
	int				counter_last_meal;
	int				start_eating;
	int				trigger_last_meal;
	long long		timestart;
	pthread_mutex_t	lock_writes;
	pthread_mutex_t	lock_meal;
	pthread_mutex_t	all_ate;
	pthread_mutex_t	lock_died;
	pthread_mutex_t	lock_all_eat;
	pthread_mutex_t	lock_fork;
	pthread_mutex_t	lock_fill_table;
	pthread_mutex_t	lock_ok;
	pthread_mutex_t	lock_static_i;
	pthread_mutex_t	lock_mutex_fork;
	pthread_mutex_t	lock_start_trigger;
}		t_parameters;

typedef struct s_philo
{
	int				is_dead;
	int				ph_id;
	int				n_meals;
	long long		last_meal;
	t_parameters	*philo_stats;
}		t_philo;

int			check_trigger_last_meal(t_philo *philo);
int			check_start_eating(t_philo *philo);
int			check_static_i(t_philo *philo);
int			check_fork(t_philo *philo);
int			free_all(pthread_t *thread, t_philo *philo, t_parameters *param);
int			phi_eat(t_philo *philo);
int			one_philo(t_philo *philo, pthread_t *th, t_parameters *init);
int			check_for_meals_eaten(t_philo *philo);
int			check_for_meals_util(t_philo *philo);
int			check_for_chars(char *str);
int			check_imput(int ac, char **av);
int			ft_atoi(const char *str);
int			check_args(int argc, char **argv);
int			is_someone_died(t_philo *philo);
int			init_parameters(t_parameters *init, char **argv, int ac);
int			have_all_ate(t_philo *philo);
int			make_threads(t_philo *philo, t_parameters *init);
void		set_trigger_last_meal(t_philo *philo);
void		set_start_eating(t_philo *philo);
void		set_static_i(t_philo *philo);
void		print_action(t_philo *philo, char *string);
void		action(long long time, t_philo *philo);
void		set_someone_died(t_philo *philo);
void		check_if_dead(t_philo *philo);
void		set_all_eat(t_philo *philo);
void		check_if_dead(t_philo *philo);
void		*routine_thread(void *arg);
void		set_fork(t_philo *philo, int a);
void		eat_mutex_handler(t_philo *philo);
t_philo		*fill_philo(t_parameters *init);
long long	get_time(void);
void		mutex_util(t_parameters *parameter);

#endif

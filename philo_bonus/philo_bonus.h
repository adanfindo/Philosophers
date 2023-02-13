/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:55:09 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 12:57:31 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_init
{
	pthread_t	monitor;
	sem_t		*semfork;
	sem_t		*semwrite;
	sem_t		*semstop;
	sem_t		*sem_death;
	sem_t		*semeatall;
	pid_t		*pid;
	long		timestart;
	int			num_philo;
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			n_toeat;
	int			alleat;
	int			parent_pid;
	int			start_check;
}			t_init;

typedef struct s_philo
{
	long long	last_meal;
	sem_t		*sem_philos;
	t_init		*init_ph;
	int			n_meals;
	int			ph_id;
}				t_philo;

/* Utils */
int				ft_strcmp(char *s, char *str);
int				wait_for_it(t_philo *philo);
char			*ft_itoa(int n);
unsigned int	selection(int n);
void			my_signal_handler1(int i, siginfo_t *sig, void *k);
void			my_signal_handler(int i, siginfo_t *sig, void *k);
int				ft_atoi(const char *str);
void			ft_printing(t_philo *philo, char *string);
long long		ft_get_time(void);
void			ft_smart_action(long long time);
void			ft_kill_process(t_philo *philo);
/* Initialize */
int				ft_init_semaphore(t_init *init);
t_philo			*ft_fill_philo(t_init *init);
int				ft_init_philo(t_init *init, char **argv, int argc);
/* Checks */
void			*ft_death(void *arg);
void			*ft_eat_check(void *arg);
int				ft_check_for_chars(char *str);
int				ft_check_input(int ac, char **av);
int				ft_check_args(int argc, char **argv);
/* Action */
void			ft_routine(t_philo *philo);
void			*ft_monitoring(void *ptr);

#endif
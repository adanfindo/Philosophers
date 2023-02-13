/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:02:31 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 13:26:55 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_mutex_handler(t_philo *philo)
{
	if (check_static_i(philo) < philo->philo_stats->num_of_philos)
	{	
		pthread_mutex_lock(&philo->philo_stats->lock_ok);
		set_static_i(philo);
		if (check_static_i(philo) == philo->philo_stats->num_of_philos)
		{
			philo->philo_stats->timestart = get_time();
			set_start_eating(philo);
			pthread_mutex_unlock(&philo->philo_stats->lock_ok);
		}
		if (check_static_i(philo) < philo->philo_stats->num_of_philos)
		{
			pthread_mutex_unlock(&philo->philo_stats->lock_ok);
			while (!check_start_eating(philo))
				usleep(100);
			set_static_i(philo);
		}
		pthread_mutex_lock(&philo->philo_stats->lock_meal);
		philo->last_meal = get_time();
		philo->philo_stats->counter_last_meal++;
		if (philo->philo_stats->counter_last_meal
			== philo->philo_stats->num_of_philos)
			set_trigger_last_meal(philo);
		pthread_mutex_unlock(&philo->philo_stats->lock_meal);
	}
}

int	phi_eat(t_philo *philo)
{
	eat_mutex_handler(philo);
	pthread_mutex_lock(&philo->philo_stats->lock_fork);
	if (check_fork(philo) == 1)
	{
		pthread_mutex_unlock(&philo->philo_stats->lock_mutex_fork);
		pthread_mutex_unlock(&philo->philo_stats->lock_fork);
		return (1);
	}
	set_fork(philo, 1);
	pthread_mutex_unlock(&philo->philo_stats->lock_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->philo_stats->lock_meal);
	print_action(philo, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_stats->lock_meal);
	action(philo->philo_stats->to_eat, philo);
	philo->n_meals++;
	set_fork(philo, 0);
	return (0);
}

int	one_philo(t_philo *philo, pthread_t *th, t_parameters *param)
{
	int	a;

	a = 1;
	philo->philo_stats->timestart = get_time();
	philo->last_meal = get_time();
	print_action(philo, "has taken a fork");
	usleep(philo->philo_stats->to_die * 1000);
	print_action(philo, "died");
	a = pthread_mutex_destroy(&param->lock_start_trigger);
	a = pthread_mutex_destroy(&param->lock_all_eat);
	a = pthread_mutex_destroy(&param->lock_died);
	a = pthread_mutex_destroy(&param->lock_fill_table);
	a = pthread_mutex_destroy(&param->lock_fork);
	a = pthread_mutex_destroy(&param->lock_meal);
	a = pthread_mutex_destroy(&param->lock_ok);
	a = pthread_mutex_destroy(&param->lock_writes);
	a = pthread_mutex_destroy(&param->all_ate);
	a = pthread_mutex_destroy(&param->lock_mutex_fork);
	a = pthread_mutex_destroy(&param->lock_static_i);
	if (a)
		return (printf("Error: Mutex not Destroyed!!\n"));
	free(th);
	free(param->fork);
	free(philo);
	return (0);
}

int	check_for_meals_eaten(t_philo *philo)
{
	if (philo->philo_stats->times_to_eat < 0
		|| philo->n_meals < philo->philo_stats->times_to_eat)
	{
		if (phi_eat(philo))
			return (2);
		if (philo->n_meals == philo->philo_stats->times_to_eat)
		{
			pthread_mutex_lock(&philo->philo_stats->all_ate);
			set_all_eat(philo);
			if (philo->philo_stats->all_eat
				== philo->philo_stats->num_of_philos)
			{
				set_someone_died(philo);
				pthread_mutex_unlock(&philo->philo_stats->all_ate);
				return (1);
			}
			pthread_mutex_unlock(&philo->philo_stats->all_ate);
		}
	}
	else
		if (check_for_meals_util(philo))
			return (1);
	return (0);
}

int	check_for_meals_util(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_stats->all_ate);
	if (philo->philo_stats->all_eat == philo->philo_stats->num_of_philos)
	{
		pthread_mutex_unlock(&philo->philo_stats->all_ate);
		return (1);
	}
	pthread_mutex_unlock(&philo->philo_stats->all_ate);
	return (0);
}

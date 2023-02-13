/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:02:49 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 13:25:49 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_static_i(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_stats->lock_static_i);
	philo->philo_stats->counter++;
	pthread_mutex_unlock(&philo->philo_stats->lock_static_i);
}

int	check_static_i(t_philo *philo)
{
	int	a;

	pthread_mutex_lock(&philo->philo_stats->lock_static_i);
	a = philo->philo_stats->counter;
	pthread_mutex_unlock(&philo->philo_stats->lock_static_i);
	return (a);
}

void	set_fork(t_philo *philo, int a)
{
	pthread_mutex_lock(&philo->philo_stats->lock_mutex_fork);
	philo->philo_stats->fork[philo->ph_id] = a;
	pthread_mutex_unlock(&philo->philo_stats->lock_mutex_fork);
	return ;
}

int	check_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_stats->lock_mutex_fork);
	if (philo->ph_id == 1)
	{
		if (philo->philo_stats->fork[philo->philo_stats->num_of_philos])
			return (1);
		else if (philo->philo_stats->fork[philo->ph_id + 1])
			return (1);
	}
	else if (philo->ph_id == philo->philo_stats->num_of_philos)
	{
		if (philo->philo_stats->fork[philo->ph_id - 1])
			return (1);
		else if (philo->philo_stats->fork[1])
			return (1);
	}
	else
	{
		if (philo->philo_stats->fork[philo->ph_id - 1])
			return (1);
		else if (philo->philo_stats->fork[philo->ph_id + 1])
			return (1);
	}
	pthread_mutex_unlock(&philo->philo_stats->lock_mutex_fork);
	return (0);
}

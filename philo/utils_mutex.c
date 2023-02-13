/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:02:52 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 13:22:28 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_died(t_philo *philo)
{
	int	someone_died;

	pthread_mutex_lock(&philo->philo_stats->lock_died);
	someone_died = philo->philo_stats->someone_died;
	pthread_mutex_unlock(&philo->philo_stats->lock_died);
	return (someone_died);
}

void	set_someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_stats->lock_died);
	philo->philo_stats->someone_died = 1;
	pthread_mutex_unlock(&philo->philo_stats->lock_died);
}

int	have_all_ate(t_philo *philo)
{
	int	all_eat;

	pthread_mutex_lock(&philo->philo_stats->lock_all_eat);
	all_eat = philo->philo_stats->all_eat;
	pthread_mutex_unlock(&philo->philo_stats->lock_all_eat);
	return (all_eat);
}

void	set_all_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_stats->lock_all_eat);
	philo->philo_stats->all_eat++;
	pthread_mutex_unlock(&philo->philo_stats->lock_all_eat);
}

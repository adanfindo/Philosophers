/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:02:56 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 13:21:08 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *string)
{
	long long	current;

	current = get_time() - philo->philo_stats->timestart;
	pthread_mutex_lock(&philo->philo_stats->lock_writes);
	if (!is_someone_died(philo))
		printf("%lld %d %s\n", current, philo->ph_id, string);
	pthread_mutex_unlock(&philo->philo_stats->lock_writes);
}

void	action(long long time, t_philo *philo)
{
	long long	past;

	past = get_time();
	while (!is_someone_died(philo))
	{
		if (get_time() - past >= time)
			break ;
		usleep(100);
	}
	return ;
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10;
		result = result + (*str - 48);
		str++;
	}
	return (result * sign);
}

int	free_all(pthread_t *thread, t_philo *philo, t_parameters *param)
{
	int	a;

	a = 1;
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
	free(thread);
	free(param->fork);
	free(philo);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:55:02 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 13:01:14 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_smart_action(long long time)
{
	long long	past;

	past = ft_get_time();
	while (1)
	{
		if (ft_get_time() - past >= time)
			break ;
		usleep(100);
	}
	return ;
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	ft_printing(t_philo *philo, char *string)
{
	long long	current;

	current = ft_get_time() - philo->init_ph->timestart;
	if (!(ft_strcmp(string, "died")))
	{
		sem_wait(philo->init_ph->semwrite);
		printf("%lld %d %s\n", current, philo->ph_id, string);
		return ;
	}
	sem_wait(philo->init_ph->semwrite);
	printf("%lld %d %s\n", current, philo->ph_id, string);
	sem_post(philo->init_ph->semwrite);
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

int	wait_for_it(t_philo *philo)
{
	int	i;
	int	k;

	i = -1;
	while (++i < philo->init_ph->num_philo + 1)
	{
		waitpid(-1, NULL, 0);
	}
	if (philo->init_ph->n_toeat > 0)
		sem_close(philo->init_ph->semeatall);
	sem_close(philo->init_ph->sem_death);
	sem_close(philo->init_ph->semfork);
	sem_close(philo->init_ph->semstop);
	sem_close(philo->init_ph->semwrite);
	k = -1;
	while (++k < philo->init_ph->num_philo)
		sem_close(philo[k].sem_philos);
	free(philo->init_ph->pid);
	free(philo);
	return (0);
}

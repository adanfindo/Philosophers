/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:02:35 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 13:27:21 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_if_dead(t_philo *philo)
{
	int		i;

	while (!have_all_ate(philo))
	{
		i = -1;
		while (++i < philo->philo_stats->num_of_philos)
		{
			pthread_mutex_lock(&philo->philo_stats->lock_meal);
			if (get_time() - philo[i].last_meal > philo->philo_stats->to_die)
			{
				print_action(&philo[i], "died");
				philo->philo_stats->all_eat = 1;
				set_someone_died(philo);
				pthread_mutex_unlock(&philo->philo_stats->lock_meal);
				break ;
			}
			pthread_mutex_unlock(&philo->philo_stats->lock_meal);
			usleep(100);
		}
	}
	return ;
}

void	*routine_thread(void *arg)
{
	t_philo	*philo;
	int		a;

	philo = (t_philo *)arg;
	while (!is_someone_died(philo))
	{
		a = check_for_meals_eaten(philo);
		if (a == 2)
		{
			usleep(50);
			continue ;
		}
		if (a == 1)
			break ;
		print_action(philo, "Is sleeping");
		action(philo->philo_stats->to_sleep, philo);
		print_action(philo, "Is thinking");
		if (philo->n_meals == philo->philo_stats->times_to_eat)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	make_threads(t_philo *philo, t_parameters *init)
{
	int			i;
	pthread_t	*th;

	i = -1;
	th = malloc(sizeof(pthread_t) * philo->philo_stats->num_of_philos);
	if (!th)
		return (1);
	if (philo->philo_stats->num_of_philos == 1)
		return (one_philo(philo, th, init));
	while (++i < philo->philo_stats->num_of_philos)
		if (pthread_create(&th[i], NULL, routine_thread, &philo[i]))
			return (printf("Error: Thread not created!!\n"));
	while (!check_trigger_last_meal(philo))
		usleep(100);
	check_if_dead(philo);
	i = -1;
	while (++i < philo->philo_stats->num_of_philos)
		if (pthread_join(th[i], NULL))
			return (printf("Error: Thread not Joined!!\n"));
	if (free_all(th, philo, init))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_parameters	init;
	t_philo			*philo;

	if (check_imput(argc, argv))
		return (0);
	if (!init_parameters(&init, argv, argc))
		return (0);
	philo = fill_philo(&init);
	if (make_threads(philo, &init))
	{
		free(init.fork);
		free(philo);
	}
	return (0);
}

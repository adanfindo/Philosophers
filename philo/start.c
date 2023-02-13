/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:02:42 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 13:20:13 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	if (argc > 4 && argc <= 6)
	{
		if (ft_atoi(argv[1]) < 1)
			return (printf("Error: You need at least one phisolopher!\n"));
		if (ft_atoi(argv[2]) < 1)
			return (printf("Error: time_to_die must be at least 1 ms and \
not higher then Max int!\n"));
		if (ft_atoi(argv[3]) < 1)
			return (printf("Error: time_to_eat must be at least 1 ms and \
not higher then Max int!\n"));
		if (ft_atoi(argv[4]) < 1)
			return (printf("Error: time_to_sleep must be at least 1 ms and \
not higher then Max int!\n"));
		if (argc == 6 && ft_atoi(argv[5]) < 1)
			return (printf("Error: number_of_times_each_philosopher_must_eat \
must be at least 1!\n"));
	}
	else
		return (printf("INVALID ARGUMENT! You need to give at least 4 args: \
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep \
and optional number_of_times_each_philosopher_must_eat\n"));
	return (0);
}

t_philo	*fill_philo(t_parameters *parameter)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i <= parameter->num_of_philos)
		parameter->fork[i] = 0;
	philo = malloc(sizeof(t_philo) * parameter->num_of_philos);
	i = -1;
	while (++i < parameter->num_of_philos)
	{
		philo[i].is_dead = 0;
		philo[i].ph_id = i + 1;
		philo[i].last_meal = 0;
		philo[i].n_meals = 0;
		philo[i].philo_stats = parameter;
	}
	return (philo);
}

int	init_parameters(t_parameters *parameter, char **argv, int ac)
{
	parameter->num_of_philos = ft_atoi(argv[1]);
	parameter->to_die = ft_atoi(argv[2]);
	parameter->to_eat = ft_atoi(argv[3]);
	parameter->to_sleep = ft_atoi(argv[4]);
	parameter->all_eat = 0;
	parameter->someone_died = 0;
	parameter->counter = 0;
	parameter->start_eating = 0;
	parameter->counter_last_meal = 0;
	parameter->trigger_last_meal = 0;
	parameter->fork = malloc(sizeof(int) * parameter->num_of_philos);
	mutex_util(parameter);
	if (ac == 6)
		parameter->times_to_eat = ft_atoi(argv[5]);
	else
		parameter->times_to_eat = -1;
	return (1);
}

int	check_for_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int	check_imput(int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i] && i < ac)
	{
		if (check_for_chars(av[i]))
			return (printf("Error: check the imput for wrong characters!\n"));
		i++;
	}
	if (check_args(ac, av))
		return (1);
	return (0);
}

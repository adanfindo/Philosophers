/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:54:53 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 12:57:31 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philo(t_init *init, char **argv, int argc)
{
	init->num_philo = ft_atoi(argv[1]);
	init->to_die = ft_atoi(argv[2]);
	init->to_eat = ft_atoi(argv[3]);
	init->to_sleep = ft_atoi(argv[4]);
	init->pid = malloc(sizeof(pid_t) * init->num_philo);
	init->alleat = 0;
	init->start_check = 0;
	if (argc == 6)
		init->n_toeat = ft_atoi(argv[5]);
	else
		init->n_toeat = -1;
	if (ft_init_semaphore(init) != 0)
		return (0);
	return (1);
}

int	ft_init_semaphore(t_init *init)
{
	sem_unlink("semfork");
	sem_unlink("semwrite");
	sem_unlink("semstop");
	sem_unlink("semeatall");
	sem_unlink("sem_death");
	init->semfork = sem_open("semfork", O_CREAT, 0644, init->num_philo / 2);
	init->semwrite = sem_open("semwrite", O_CREAT, 0644, 1);
	init->semstop = sem_open("semstop", O_CREAT, 0644, 1);
	init->sem_death = sem_open("sem_death", O_CREAT, 0644, 1);
	if (init->semfork == SEM_FAILED || init->semwrite == SEM_FAILED \
		|| init->semstop == SEM_FAILED || init->sem_death == SEM_FAILED)
		return (printf("Error sem_open!"));
	if (init->n_toeat > 0)
	{
		init->semeatall = sem_open("semeatall", O_CREAT, 0644, 0);
		if (init->semeatall == SEM_FAILED)
			return (printf("Error sem_open!"));
	}
	return (0);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc > 4 && argc <= 6)
	{
		if (ft_atoi(argv[1]) < 1)
			return (printf("Error: At least one phisolopher needed!\n"));
		if (ft_atoi(argv[2]) < 1)
			return (printf("Error: time_to_die must be at least 1 ms and\
not higher then Max int!\n"));
		if (ft_atoi(argv[3]) < 1)
			return (printf("Error: time_to_eat must be at least 1 ms and\
not higher then Max int!\n"));
		if (ft_atoi(argv[4]) < 1)
			return (printf("Error: time_to_sleep must be at least 1 ms and\
not higher then Max int!\n"));
		if (argc == 6 && ft_atoi(argv[5]) < 1)
			return (printf("Error: number_of_times_each_philosopher_must_eat \
must be at least 1!\n"));
	}
	else
		return (printf("Error: INVALID ARGUMENT! You need to compile with: \
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep \
and optional number_of_times_each_philosopher_must_eat\n"));
	return (0);
}

int	ft_check_for_chars(char *str)
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

int	ft_check_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i] && i < ac)
	{
		if (ft_check_for_chars(av[i]))
			return (printf("Error: check the input for wrong characters!\n"));
		i++;
	}
	if (ft_check_args(ac, av))
		return (1);
	return (0);
}

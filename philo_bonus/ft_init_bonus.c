/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:54:56 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 12:57:31 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*ft_fill_philo(t_init *init)
{
	int		i;
	t_philo	*philo;
	char	*s;

	i = 0;
	philo = malloc(sizeof(t_philo) * init->num_philo);
	while (i < init->num_philo)
	{
		philo[i].ph_id = i + 1;
		philo[i].last_meal = 0;
		philo[i].n_meals = 0;
		philo[i].init_ph = init;
		s = ft_itoa(philo[i].ph_id);
		sem_unlink(s);
		philo[i].sem_philos = sem_open(s, O_CREAT, 0644, 1);
		free(s);
		i++;
	}
	return (philo);
}

void	my_signal_handler(int i, siginfo_t *sig, void *k)
{
	return ;
}

void	my_signal_handler1(int i, siginfo_t *sig, void *k)
{
	exit(0);
	return ;
}

unsigned int	selection(int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	number;
	unsigned int	a;
	char			*string;

	a = selection(n);
	number = n;
	if (n < 0)
	{
		number *= -1;
		a++;
	}
	string = malloc(sizeof(char) * (a + 1));
	if (!string)
		return (NULL);
	*(string + a) = '\0';
	while (a-- != 0)
	{
		*(string + a) = (number % 10) + '0';
		number = number / 10;
	}
	if (n < 0)
		*(string + 0) = '-';
	return (string);
}

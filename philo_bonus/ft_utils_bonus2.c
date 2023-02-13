/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afindo <afindo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:55:05 by afindo            #+#    #+#             */
/*   Updated: 2022/05/10 12:57:31 by afindo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(char *s, char *str)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != str[i])
			return (1);
	}
	return (0);
}

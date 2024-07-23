/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:58:54 by capapes           #+#    #+#             */
/*   Updated: 2024/07/18 16:32:47 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "philo.h"
#include "philo_helpers.h"

void	set_error(t_philo *philo)
{
	int	unlock;

	unlock = 1;
	if (pthread_mutex_lock(&philo->program->mx_write))
		unlock = 0;
	philo->err = 1;
	if (unlock)
		pthread_mutex_unlock(&philo->program->mx_write);
}

inline int	check_philo_end(t_program *program, t_philo *philo)
{
	return (program->philos_end
		&& (philo->err = 1));
}

int	philo_exit(t_philo *philo, int err)
{
	err & PHILO_ERR_WRITE && pthread_mutex_unlock(&philo->program->mx_write);
	err & PHILO_ERR_FIRST && pthread_mutex_unlock(philo->fork_first);
	err & PHILO_ERR_FORKS_UN && pthread_mutex_unlock(philo->fork_first);
	err & PHILO_ERR_FORKS_UN && pthread_mutex_unlock(philo->fork_second);
	return (1);
}

int	philo_exit_print(t_philo *philo, int err)
{
	set_error(philo);
	philo_exit(philo, err);
	return (1);
}

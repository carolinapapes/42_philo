/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos__init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capapes <capapes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:32:08 by carolinapap       #+#    #+#             */
/*   Updated: 2024/07/17 17:11:23 by capapes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "philo.h"
#include "philo_helpers.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	_allocate(t_program *program)
{
	program->philos = malloc(sizeof(t_philo) * program->philos_n);
	if (!program->philos)
		return (program__exit(program, 0, CLEAN_PROGRAM_MX, EXIT_FAILURE));
	memset(program->philos, 0, sizeof(t_philo) * program->philos_n);
	return (0);
}

static int	_philo__th_create(t_program *program, int i)
{
	if (pthread_create(&program->philos[i].id, NULL, \
		(void *)philo__rutine, &program->philos[i]))
		return (program__exit(program, i, CLEAN_START, EXIT_FAILURE));
	return (0);
}

int	philos__init(t_program *program)
{
	return (\
	(_allocate(program) && (ft_puterr(ERR_MALLOC), 1)) || \
	(philos__iter(program, 0, philo__init) && ft_puterr(ERR_MUTEX)) || \
	(philos__iter(program, 0, _philo__th_create) && ft_puterr(ERR_THREAD)) \
	);
}

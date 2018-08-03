/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:21:00 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/03 14:51:26 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handle(int sig)
{
	char	**env;

	env = NULL;
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		prompt(ENV);
	}
}

void	ignore_child_signal(int sig)
{
	if (sig == SIGINT)
		ft_putchar('\n');
}

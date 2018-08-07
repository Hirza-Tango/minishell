/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:21:00 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/07 21:32:35 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handle(int sig)
{
	char	**env;

	env = NULL;
	(void)env;
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

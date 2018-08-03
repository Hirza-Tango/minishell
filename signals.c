/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 11:25:57 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/03 11:28:35 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_handle(int sig)
{
	if (sig == SIGINT)
		ft_putchar('\n');
	signal(SIGINT, signal_handle);
}

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
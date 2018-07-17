/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 14:29:55 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/17 11:55:18 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		mini_echo(char *argv[])
{
	argv++;
	while (*argv)
	{
		ft_putstr(*argv);
		ft_putchar(' ');
		argv++;
	}
	ft_putstr("\b\n");
	return (0);
}

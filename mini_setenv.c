/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:21:15 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/10 17:40:25 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_setenv(char *argv[])
{
	char	*var;

	argv++;
	if (!*argv)
	{
		mini_env(argv);
		return ;
	}
	var = *argv++;
	if (*argv)
		ft_setenv(var, *argv, 1);//TODO: Maybe null check is handled?
	else
		ft_setenv(var, "", 1);
}

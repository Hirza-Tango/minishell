/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:21:15 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/13 18:11:46 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
int		mini_setenv(char *argv[], char *env[])
{
	if (!argv[1])
	{
		mini_env(argv, env);
		return (0);
	}
	ft_setenv(argv[1], argv[2] ? argv[2] : "", env);
	return (0);
}

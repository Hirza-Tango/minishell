/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:31:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/23 14:39:39 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		mini_unsetenv(char *argv[], char ***env)
{
	if (argv[1])
		return (ft_unsetenv(argv[1], env));
	return (0);
}

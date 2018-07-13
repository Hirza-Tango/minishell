/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:17:53 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/13 15:29:48 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		mini_pwd(void)
{
	char	*wd;

	if (!(wd = getcwd(NULL, 0)))
		return (1);
	ft_putendl(wd);
	free(wd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:29:30 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/23 14:51:17 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		mini_env(char *argv[], char ***env)
{
	char		*name;
	char		*value;
	char		*pos;
	char		**dup;
	int			status;

	argv++;
	dup = ft_tabdup(*env);
	while (*argv && (pos = ft_strchr(*argv, '=')))
	{
		name = ft_strndup(*argv, pos - *argv);
		value = ft_strdup(pos + 1);
		ft_setenv(name, value, &dup);
		free(name);
		free(value);
		argv++;
	}
	if (!*argv || !**argv)
	{
		while (*dup)
			ft_putendl(*dup++);
		status = 0;
	}
	else
		status = mini_launch(argv, dup);
	ft_tabfree(dup);
	return (status);
}

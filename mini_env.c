/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:29:30 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/17 12:02:02 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		mini_env(char *argv[], char *env[])
{
	char		*name;
	char		*value;
	char		*pos;
	char		**dup;

	argv++;
	while (*argv && (pos = ft_strchr(*argv, '=')))
	{
		name = ft_strndup(*argv, pos - *argv);
		value = ft_strdup(pos + 1);
		ft_setenv(name, value, &env);
		free(name);
		free(value);
		argv++;
	}
	if (!*argv || !**argv)
	{
		dup = env;
		while (*dup)
			ft_putendl(*dup++);
	}
	else
		return (mini_launch(argv, env));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:29:30 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/13 17:19:54 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
int		mini_env(char *argv[], char *env[])
{
	char		*name;
	char		*value;
	char		*pos;
	char		**dup;

	//TODO: Handle quoting
	argv++;
	while (*argv && (pos = ft_strchr(*argv, '=')))
	{
		ft_putendl("DEBUG: Equals");
		name = ft_strndup(*argv, pos - *argv);
		value = ft_strdup(pos + 1);
		ft_setenv(name, value, env);
		ft_putendl("Env was set");
		free(name);
		free(value);
		argv++;
	}
	if (!*argv || !**argv)
	{
		ft_putendl("DEBUG: No arg");
		dup = env;
		while (*dup)
			ft_putendl(*dup++);
	}
	else
	{
		ft_putendl("DEBUG: Arg");
		return (mini_launch(argv, env));
	}
	return (0);
}

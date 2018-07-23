/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:29:30 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/23 17:01:17 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_env(char *env_string, char *pos, char ***env)
{
	char	*name;
	char	*value;

	name = ft_strndup(env_string, pos - env_string);
	value = ft_strdup(pos + 1);
	ft_setenv(name, value, env);
	free(name);
	free(value);
}

int			mini_env(char *argv[], char ***env)
{
	char		*pos;
	char		**dup;
	int			status;

	argv++;
	dup = ft_tabdup(*env);
	while (*argv && (pos = ft_strchr(*argv, '=')))
	{
		set_env(*argv, pos, &dup);
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

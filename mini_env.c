/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:29:30 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/10 17:39:34 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_env(char *argv[])
{
	char		*name;
	char		*value;
	char		*pos;
	char		**dup;
	extern char	**environ;

	argv++;
	//TODO: Handle -i
	//TODO: Handle quoting
	while ((pos = ft_strchr(*argv, '=')))
	{
		name = ft_strndup(*argv, pos - *argv);
		value = ft_strdup(pos + 1);
		ft_setenv(name, value, 1);
		free(name);
		free(value);
		argv++;
	}
	if (*argv)
		mini_launch(argv);
	else
	{
		dup = environ;
		while (*dup)
			ft_putendl(*dup++);
	}
}

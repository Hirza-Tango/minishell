/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 16:29:30 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/11 15:10:05 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_env(char *argv[], char *env[])
{
	//char		*name;
	//char		*value;
	//char		*pos;
	char		**dup;

	argv++;
	//TODO: Handle -i
	//TODO: Handle quoting
	/*while ((pos = ft_strchr(*argv, '=')))
	{
		ft_putendl("DEBUG: Equals");
		name = ft_strndup(*argv, pos - *argv);
		value = ft_strdup(pos + 1);
		ft_setenv(name, value, 1, env);
		ft_putendl("Env was set");
		free(name);
		free(value);
		argv++;
	}*/
	ft_putendl(ft_itoa_base((long long int)env, 16));
	if (!*argv || !**argv)
	{
		ft_putendl("DEBUG: No args");
		dup = env;
		while (*dup)
			ft_putendl(*dup++);
	}
	else
		ft_putendl("DEBUG: Args"); //mini_launch(argv);
}

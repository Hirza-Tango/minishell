/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 16:47:58 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/13 18:09:50 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	env_replace(const char *name, const char *value, char **env)
{
	while (*env)
	{
		ft_putendl("DEBUG:\n");
		ft_putnbr((long int)*env);
		ft_putchar('\n');
		if (!ft_strncmp(name, *env, ft_strlen(name)) &&
			(*env)[ft_strlen(name)] == '=')
		{
			free(*env);
			*env = ft_strnew(ft_strlen(name) + ft_strlen(value) + 2);
			ft_putnbr((intmax_t)*env);
			ft_putchar('\n');
			*env = ft_strcat(ft_strcat(ft_strcpy(*env, name), "="), value);
			ft_putendl(*env);
		}
		env++;
	}
	return (0);
}

static int	env_add(const char *name, const char *value, char ***env)
{
	char 	**ret;
	char 	**dup;
	char	**retdup;
	size_t	size;

	dup = *env;
	size = 0;
	while (*dup)
	{
		if (ft_strncmp(name, *dup, ft_strlen(name))
			|| (*dup)[ft_strlen(name)] != '=')
			size++;
		dup++;
	}
	ret = malloc(sizeof(char *) * (size + 1));
	dup = *env;
	retdup = ret;
	while (*dup)
	{
		if (ft_strncmp(name, *dup, ft_strlen(name))
			|| (*dup)[ft_strlen(name)] != '=')
			*retdup++ = *dup;
		dup++;
	}
	*retdup = NULL;
	*env = ret;
	return (0);
}

int			ft_setenv(const char *name, const char *value, char **env)
{
	ft_putendl("Finding...");
	if (ft_getenv(name, env))
	{
		ft_putendl("Replacing..");
		return (env_replace(name, value, env));
	}
	else
	{
		ft_putendl("Adding...");
		return (env_add(name, value, &env));
	}
}
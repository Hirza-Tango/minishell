/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 16:47:58 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/02 17:45:28 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	env_replace(const char *name, const char *value, char **env)
{
	while (*env)
	{
		if (!ft_strncmp(name, *env, ft_strlen(name)) &&
			(*env)[ft_strlen(name)] == '=')
		{
			free(*env);
			*env = ft_strmjoin(3, name, "=", value);
		}
		env++;
	}
	return (0);
}

static int	env_add(const char *name, const char *value, char ***env)
{
	char	**ret;
	char	**dup;
	char	**retdup;
	size_t	size;

	dup = *env;
	size = 0;
	while (*(dup++))
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 2));
	dup = *env;
	retdup = ret;
	while (*dup)
		*retdup++ = *dup++;
	free(*env);
	*retdup++ = ft_strmjoin(3, name, "=", value);
	*retdup = NULL;
	*env = ret;
	return (0);
}

int			ft_setenv(const char *name, const char *value, char ***env)
{
	if (!*env)
		return (1);
	if (ft_getenv(name, *env))
		return (env_replace(name, value, *env));
	else
		return (env_add(name, value, env));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 17:20:51 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/31 18:03:45 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**newdup(const char *name, size_t size, char ***env)
{
	char	**ret;
	char	**dup;
	char	**retdup;

	ret = malloc(sizeof(char *) * (size + 1));
	dup = *env;
	retdup = ret;
	while (*dup)
	{
		if (ft_strncmp(name, *dup, ft_strlen(name)) ||
			(*dup)[ft_strlen(name)] != '=')
			*(retdup++) = *dup;
		else
			free(*dup);
		dup++;
	}
	free(*env);
	*retdup = NULL;
	return (ret);
}

int			ft_unsetenv(const char *name, char ***env)
{
	size_t	size;
	char	**dup;

	dup = *env;
	size = 0;
	while (*dup)
	{
		if (ft_strncmp(name, *dup, ft_strlen(name)) ||
			(*dup)[ft_strlen(name)] != '=')
			size++;
		dup++;
	}
	*env = newdup(name, size, env);
	return (0);
}

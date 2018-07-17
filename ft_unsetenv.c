/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 17:20:51 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/17 09:45:07 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unsetenv(const char *name, char ***env)
{
	char	**ret;
	char	**dup;
	char	**retdup;
	size_t	size;

	dup = *env;
	size = 0;
	while (*dup)
	{
		if (ft_strnequ(name, *dup, ft_strlen(name)) &&
			(*dup)[ft_strlen(name)] == '=')
			size++;
		dup++;
	}
	ret = malloc(sizeof(char *) * (size + 1));
	dup = *env;
	retdup = ret;
	while (*dup)
	{
		if (ft_strnequ(name, *dup, ft_strlen(name)) &&
			(*dup)[ft_strlen(name)] == '=')
			*(retdup++) = *dup;
		else
			free(*dup);
		dup++;
	}
	free(*env);
	*retdup = NULL;
	*env = ret;
	return (0);
}

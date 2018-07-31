/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:51:34 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/31 17:35:00 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		default_path(char ***env)
{
	const int	fd = open("/etc/paths", O_RDONLY);
	char		*input;
	char		*path;
	char		*temp;

	path = NULL;
	while (get_next_line(fd, &input) > 0)
	{
		if (path)
		{
			temp = ft_strmjoin(3, path, ":", input);
			free(path);
			path = temp;
		}
		else
			path = input;
	}
	ft_setenv("PATH", path, env);
	close(fd);
	return (0);
}

char	*abs_to_rel(char *old, char **env, int reverse)
{
	const char	*find = reverse ? "~" : ft_getenv("HOME", env);
	const char	*replace = (!reverse) ? "~" : ft_getenv("HOME", env);

	if (!ft_strncmp(old, find, ft_strlen(find)))
		return (ft_strjoin(replace, old + ft_strlen(find)));
	return (ft_strdup(old));
}

void	substitutions(char **tab, char **env)
{
	while (*tab)
	{
		if (**tab == '~')
			ft_swapnfree(tab, abs_to_rel(*tab, env, 1));
		if (**tab == '$' && (*tab)[1] != '?' && (*tab)[1] != '@')
			ft_swapnfree(tab, ft_getenv(*tab + 1, env) ?
				ft_strdup(ft_getenv(*tab + 1, env)) : ft_strdup(""));
		tab++;
	}
}

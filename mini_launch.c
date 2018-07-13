/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 12:46:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/13 15:59:28 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_tabfree(char **tab)
{
	char	**dup;

	if (!tab)
		return ;
	dup = tab;
	while (*dup)
		free(*dup++);
	tab = NULL;
}

int		mini_launch(char *argv[], char *env[])
{
	char	**path;
	char	**dup;
	char	*exec;
	pid_t	pid;
	int		status;

	status = 0;
	path = ft_strsplit(ft_getenv("PATH", env), ':');
	dup = path;
	while (*dup)
	{
		exec = ft_strnew(ft_strlen(*dup) + ft_strlen(argv[0]) + 2);
		exec = ft_strcat(ft_strcat(ft_strcat(exec, *dup), "/"), argv[0]);
		if (!access(exec, X_OK))
			break ;
		free(exec);
		exec = NULL;
		dup++;
	}
	ft_tabfree(path);
	if (!exec)
	{
		return (ft_puterr(SHELL_NAME, argv[0], "command not found", 1));
	}
	if ((pid = fork()))
	{
		wait4(pid, &status, 0, NULL);
		free(exec);
		return (status);
	}
	else
	{
		execve(exec, argv, env);
		exit (-1);
	}
}

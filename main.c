/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:16:43 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/13 18:09:18 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_puterr(const char *command, const char *target, const char *reason,
	int code)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (*target)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(reason, 2);
	return (code);
}

void	ft_tabfree(char **tab)
{
	char	**dup;

	if (!tab)
		return ;
	dup = tab;
	while (*dup)
		free(*dup++);
	tab = NULL;
}

void	terminate(int sig)
{
	if (sig == 15)
		exit(0);
}

void	call_handler(char *argv[], char *env[], int *status)
{
	if (ft_strequ(argv[0], "echo"))
		*status = mini_echo(argv);
	else if (ft_strequ(argv[0], "cd"))
		*status = mini_cd(argv, env);
	else if (ft_strequ(argv[0], "pwd"))
		*status = mini_pwd();
	else if (ft_strequ(argv[0], "setenv"))
		*status = mini_setenv(argv, env);
	/*else if (ft_strequ(argv[0], "unsetenv"))
		*status = mini_unsetenv(argv, env);*/
	else if (ft_strequ(argv[0], "env"))
		*status = mini_env(argv, env);
	else if (ft_strequ(argv[0], "exit") || ft_strequ(argv[0], "q"))
	{
		ft_tabfree(env);
		exit (argv[1] ? ft_atoi(argv[1]) : 0);
	}
	else if (ft_strequ(argv[0], "$?"))
	{
		ft_putnbr(*status);
		ft_putchar('\n');
	}
	else
		mini_launch(argv, env);
}

int		main(int argc, char *argv[], char *envv[])
{
	char	*input;
	int		status;
	char	**args;
	char	**env;

	env = ft_tabdup(envv);
	(void)(argv && argc);
	status = 0;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		ft_putstr("$> ");
		if (get_next_line(0, &input) <= 0)
		{
			ft_tabfree(env);
			ft_putendl("exit");
			exit(0);
		}
		if (!(args = ft_strsplit(input, ' ')))
			continue;
		//TODO: split on all whitespace
		call_handler(args, env, &status);
		ft_tabfree(args);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:16:43 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/07 21:32:31 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**init_env(char **env)
{
	char	**ret;
	char	*newlvl;

	ret = ft_tabdup(env);
	if (!ft_getenv("PATH", ret))
		default_path(&ret);
	ft_setenv("SHELL", ft_getenv("_", ret), &ret);
	newlvl = ft_itoa(ft_atoi(ft_getenv("SHLVL", ret)) + 1);
	ft_setenv("SHLVL", newlvl, &ret);
	free(newlvl);
	return (ret);
}

static void	set_underscore(char **argv, char ***env)
{
	while (*argv)
		argv++;
	argv--;
	ft_setenv("_", *argv, env);
}

static void	call_handler(char *argv[], char ***env, int *status)
{
	if (ft_strequ(argv[0], "echo"))
		*status = mini_echo(argv);
	else if (ft_strequ(argv[0], "cd"))
		*status = mini_cd(argv, env);
	else if (ft_strequ(argv[0], "pwd"))
		*status = mini_pwd();
	else if (ft_strequ(argv[0], "setenv"))
		*status = mini_setenv(argv, env);
	else if (ft_strequ(argv[0], "unsetenv"))
		*status = mini_unsetenv(argv, env);
	else if (ft_strequ(argv[0], "env"))
		*status = mini_env(argv, env);
	else if (ft_strequ(argv[0], "exit") || ft_strequ(argv[0], "q"))
	{
		ft_tabfree(*env);
		exit(argv[1] ? ft_atoi(argv[1]) : *status);
	}
	else if (ft_strequ(argv[0], "$?"))
	{
		ft_putnbr(*status);
		ft_putchar('\n');
	}
	else
		*status = mini_launch(argv, *env);
	set_underscore(argv, env);
}

int			input_handler(const char *input, int *status, char ***env)
{
	char		**bigargs;
	char		**dup;
	char		**args;

	if (!(bigargs = ft_strsplit(input, ';')))
		return (1);
	dup = bigargs;
	while (*dup)
	{
		if (!(args = ft_strqotsplit(*dup)))
		{
			dup++;
			continue;
		}
		substitutions(args, *env);
		call_handler(args, env, status);
		ft_tabfree(args);
		free(args);
		dup++;
	}
	ft_tabfree(bigargs);
	free(bigargs);
	return (0);
}

int			main(int argc, char *argv[], char *envv[])
{
	char		*input;
	int			status;
	char		**env;

	(void)(argv && argc);
	(void)env;
	ENV = init_env(envv);
	status = 0;
	signal(SIGINT, signal_handle);
	while (1)
	{
		prompt(ENV);
		if (get_next_line(0, &input) <= 0)
		{
			ft_putendl("exit");
			exit(status);
		}
		input_handler(input, &status, &ENV);
		free(input);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:16:43 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/31 17:49:50 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**init_env(char **env)
{
	char **ret;

	ret = ft_tabdup(env);
	if (!ft_getenv("PATH", ret))
		default_path(&ret);
	ft_setenv("SHELL", ft_getenv("_", ret), &ret);
	ft_setenv("SHLVL", ft_itoa(ft_atoi(ft_getenv("SHLVL", ret)) + 1), &ret);
	return (ret);
}

static void	prompt(char **env)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	ft_swapnfree(&wd, abs_to_rel(wd, env, 0));
	ft_putstr("\e[32m");
	ft_putstr(ft_getenv("USER", env));
	ft_putstr("\e[31m");
	ft_putstr("@");
	ft_putstr("\e[32m");
	ft_putstr(wd);
	free((char *)wd);
	ft_putstr("\e[31m");
	ft_putstr("#");
	ft_putstr("\e[0m");
	ft_putstr(" ");
}

int			ft_puterr(const char *command, const char *target,
	const char *reason, int code)
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

void		call_handler(char *argv[], char ***env, int *status)
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
}

int			main(int argc, char *argv[], char *envv[])
{
	char		*input;
	int			status;
	char		**args;
	char		**env;

	(void)(argv && argc);
	env = init_env(envv);
	status = 0;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		prompt(env);
		if (get_next_line(0, &input) <= 0)
		{
			ft_tabfree(env);
			ft_putendl("exit");
			exit(status);
		}
		if (!(args = ft_strqotsplit(input)))
			continue;
		substitutions(args, env);
		call_handler(args, &env, &status);
		ft_tabfree(args);
	}
}

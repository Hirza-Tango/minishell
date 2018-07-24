/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:16:43 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/24 10:28:40 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	set_path(char *env[])
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
	ft_setenv("PATH", path, &env);
	close(fd);
	return (0);
}

static void	prompt(char **env)
{
	const char *wd = getcwd(NULL, 0);

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

	env = ft_tabdup(envv);
	if (!getenv("PATH"))
		set_path(env);
	(void)(argv && argc);
	status = 0;
	signal(SIGINT, SIG_IGN);
	ft_setenv("SHELL", SHELL_NAME, &env);
	ft_setenv("SHLVL", ft_itoa(ft_atoi(ft_getenv("SHLVL", env)) + 1), &env);
	while (1)
	{
		prompt(env);
		if (get_next_line(0, &input) <= 0)
		{
			ft_tabfree(env);
			ft_putendl("exit");
			exit(status);
		}
		if (!(args = ft_strqotsplit(input, ' ')))
			continue;
		tilde_substitute(args, env);
		call_handler(args, &env, &status);
		ft_tabfree(args);
	}
}

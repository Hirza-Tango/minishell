/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 14:54:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/01 11:15:34 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**	TODO: Cases:
**		System:
**			EFAULT:	Path is outside process adress space
**			EIO:	IO Error
**			ELOOP:	Symlink loop
*/

static int	is_dir(const char *path)
{
	struct stat	s;

	stat(path, &s);
	if ((s.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

static int	cd(const char *path, char ***env)
{
	const char	*com = SHELL_NAME ": cd";

	if (!path)
	{
		if (chdir(ft_getenv("HOME", *env)))
			return (ft_puterr(com, "", "HOME not set", 1));
	}
	else if (ft_strlen(path) > MAXNAMLEN)
		return (ft_puterr(com, path, "File name too long", 1));
	else if (ft_strequ(path, "-"))
	{
		if (chdir(ft_getenv("OLDPWD", *env)))
			return (ft_puterr(com, "", "OLDPWD not set", 1));
	}
	else if (chdir(path))
	{
		if (access(path, F_OK))
			return (ft_puterr(com, path, "No such file or directory", 1));
		if (access(path, R_OK))
			return (ft_puterr(com, path, "Permission denied", 1));
		if (!is_dir(path))
			return (ft_puterr(com, path, "Not a directory", 1));
		return (ft_puterr(com, path, "System error", 1));
	}
	return (0);
}

int			mini_cd(char *argv[], char ***env)
{
	char		*pwd;

	pwd = getcwd(NULL, 0);
	cd(argv[1], env);
	ft_setenv("OLDPWD", pwd, env);
	free(pwd);
	pwd = getcwd(NULL, 0);
	ft_setenv("PWD", getcwd(NULL, 0), env);
	free(pwd);
	return (0);
}

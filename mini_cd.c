/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 14:54:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/03 15:43:32 by dslogrov         ###   ########.fr       */
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
	if (!path)
	{
		if (chdir(ft_getenv("HOME", *env)))
			return (ft_puterr(CD_ERR, "", "HOME not set", 1));
	}
	else if (ft_strlen(path) > MAXNAMLEN)
		return (ft_puterr(CD_ERR, path, "File name too long", 1));
	else if (ft_strequ(path, "-"))
	{
		if (chdir(ft_getenv("OLDPWD", *env)))
			return (ft_puterr(CD_ERR, "", "OLDPWD not set", 1));
		ft_putendl(ft_getenv("OLDPWD", *env));
	}
	else if (chdir(path))
	{
		if (access(path, F_OK))
			return (ft_puterr(CD_ERR, path, "No such file or directory", 1));
		if (access(path, R_OK))
			return (ft_puterr(CD_ERR, path, "Permission denied", 1));
		if (!is_dir(path))
			return (ft_puterr(CD_ERR, path, "Not a directory", 1));
		return (ft_puterr(CD_ERR, path, "System error", 1));
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
	ft_setenv("PWD", pwd, env);
	free(pwd);
	return (0);
}

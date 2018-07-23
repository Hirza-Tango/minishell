/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 14:54:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/23 16:20:57 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_dir(const char *path)
{
	struct stat	s;

	stat(path, &s);
	if ((s.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

/*
**	TODO: Cases:
**		System:
**			EFAULT:	Path is outside process adress space
**			EIO:	IO Error
**			ELOOP:	Symlink loop
*/

int			mini_cd(char *argv[], char ***env)
{
	const char	*com = SHELL_NAME ": cd";
	char		*pwd;
	const char	*path = abs_to_rel(argv[1], *env, 1);

	pwd = getcwd(NULL, 0);
	if (!path)
	{
		if (chdir(ft_getenv("HOME", *env)))
			return (ft_puterr(com, "", "HOME not set", 1));
	}
	else if (ft_strlen(argv[1]) > MAXNAMLEN)
		return (ft_puterr(com, argv[1], "File name too long", 1));
	else if (ft_strequ(path, "-"))
	{
		if (chdir(ft_getenv("OLDPWD", *env)))
			return (ft_puterr(com, "", "OLDPWD not set", 1));
	}
	else if (chdir(path))
	{
		if (access(path, F_OK))
			return (ft_puterr(com, argv[1], "No such file or directory", 1));
		if (access(path, R_OK))
			return (ft_puterr(com, argv[1], "Permission denied", 1));
		if (!is_dir(path))
			return (ft_puterr(com, argv[1], "Not a directory", 1));
		return (ft_puterr(com, argv[1], "System error", 1));
	}
	ft_setenv("OLDPWD", pwd, env);
	ft_setenv("PWD", getcwd(NULL, 0), env);
	free((char *)path);
	return (0);
}

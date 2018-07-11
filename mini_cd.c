/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 14:54:46 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/11 13:46:14 by dslogrov         ###   ########.fr       */
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

//	TODO: handle quoting
//	TODO: figure out why chdir isn't working
void		mini_cd(char *argv[], char *env[])
{
	const char	*command = SHELL_NAME ": cd";

	if (!argv[1])
	{
		if ((chdir(ft_getenv("HOME", env))))
			ft_puterr(command, "", "HOME not set");
	}
	else if (ft_strlen(argv[1]) > MAXNAMLEN)
		ft_puterr(command, argv[1], "File name too long");
	else if (ft_strequ(argv[1], "-"))
	{
		if (chdir(ft_getenv("OLDPWD", env)))
			ft_puterr(command, "", "OLDPWD not set");
	}
	else if (chdir(argv[1]))
	{
		if (access(argv[1], F_OK))
			ft_puterr(command, argv[1], "No such file or directory");
		if (access(argv[1], R_OK))
			ft_puterr(command, argv[1], "Permission denied");
		if (!is_dir(argv[1]))
			ft_puterr(command, argv[1], "Not a directory");
		ft_puterr(command, argv[1], "System error");
		//TODO: Cases:
		// System:
		//		EFAULT:	Path is outside process adress space
		//		EIO:	IO Error
		//		ELOOP:	Symlink loop
	}
}

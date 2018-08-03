/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:04:50 by dslogrov          #+#    #+#             */
/*   Updated: 2018/08/03 14:47:40 by dslogrov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <get_next_line.h>

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

# define SHELL_NAME "minishell"
# ifndef GLOBAL_ENV
#  define ENV env
# else

char	**g_env;

#  define ENV g_env
# endif

int			mini_echo(char *argv[]);
int			mini_cd(char *argv[], char ***env);
int			mini_pwd(void);
int			mini_env(char *argv[], char ***env);
int			mini_setenv(char *argv[], char ***env);
int			mini_unsetenv(char *argv[], char ***env);
int			mini_launch(char *argv[], char **env);

int			ft_puterr(const char *command, const char *target,
	const char *reason, int code);
const char	*ft_getenv(const char *name, char **env);
int			ft_setenv(const char *name, const char *value, char ***env);
int			ft_unsetenv(const char *name, char ***env);
char		*abs_to_rel(char *old, char **env, int reverse);
void		substitutions(char **tab, char **env);
int			default_path(char ***env);
void		prompt(char **env);
void		signal_handle(int sig);
void		ignore_child_signal(int sig);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:04:50 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/13 15:30:02 by dslogrov         ###   ########.fr       */
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

# ifdef CUSTOM_PROMPT
#  include <pwd.h>
#  define PS1 getpwuid
# endif

# define SHELL_NAME "minishell"

int		mini_echo(char *argv[]);
int		mini_cd(char *argv[], char *env[]);
int		mini_pwd(void);
int		mini_env(char *argv[], char *env[]);
int		mini_setenv(char *argv[], char *env[]);
int		mini_unsetenv(char *argv[], char *env[]);
int		mini_launch(char *argv[], char *env[]);

int		ft_puterr(const char *command, const char *target, const char *reason,
	int code);

#endif

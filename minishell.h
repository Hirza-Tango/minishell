/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslogrov <dslogrove@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:04:50 by dslogrov          #+#    #+#             */
/*   Updated: 2018/07/11 14:53:39 by dslogrov         ###   ########.fr       */
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
void	mini_cd(char *argv[], char *env[]);
void	mini_pwd(void);
void	mini_env(char *argv[], char *env[]);
int		mini_setenv(char *argv[], char *env[]);
void	mini_unsetenv(char *argv[], char *env[]);

void	ft_puterr(const char *command, const char *target, const char *reason);

#endif

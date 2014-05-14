/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrebierr <vrebierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 15:47:12 by vrebierr          #+#    #+#             */
/*   Updated: 2014/05/14 15:47:13 by vrebierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh2.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

static void		exec(char *path, char **av, t_env *env)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		show_error("fork: fail");
	else if (pid == 0)
		execve(path, av, env->envp);
	else
		wait(NULL);
}

static void		exec_verif(char **av, t_env *env)
{
	int			i;
	int			found;
	char		*tmp;
	struct stat	buf;

	i = 0;
	found = 0;
	while (env->paths[i] && found == 0)
	{
		tmp = ft_strjoin(ft_strjoin(env->paths[i], "/"), av[0]);
		if (stat(tmp, &buf) == 0)
			found = 1;
		else
			i++;
	}
	if (found == 0)
	{
		ft_putstr(av[0]);
		ft_putendl(": command not found");
	}
	else
		exec(tmp, av, env);
}

void			exec_cmd(char *line, t_env *env)
{
	char	**cmds;
	int		i;

	cmds = ft_strsplit(line, ';');
	i = 0;
	while (cmds[i])
	{

		exec_verif(ft_strsplit(cmds[i], ' '), env);
		i++;
	}
}

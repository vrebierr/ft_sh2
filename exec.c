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
		execve(tmp, av, env->envp);
}

void			exec_dup(char **av, int pipe_fd[2], t_env *env, int	direction)
{
	if (direction == 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		exec_verif(av, env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		exec_verif(av, env);
	}
}

static void		exec_pipe(char **av, t_env *env, char **pipes)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		i;

	if (pipe(pipe_fd) == -1)
		return (show_error("pipex: fail"));
	i = 0;
	while (pipes[i])
	{
		ft_putendl(pipes[i]);
		if ((pid = fork()) < 0)
			show_error("fork: fail");
		else if (pid == 0)
		{
			if (pipes[i + 1])
				exec_dup(av, pipe_fd, env, 0);
			else
				exec_dup(av, pipe_fd, env, 1);
			exit(0);
		}
		else
			i++;
	}
}

static void		exec_fork(char *cmd, t_env *env)
{
	pid_t	pid;
	char	**pipes;
	int		i;

	pipes = ft_strsplit(cmd, '|');
	i = 0;
	if ((pid = fork()) < 0)
		show_error("fork: fail");
	else if (pid == 0)
	{
		exec_pipe(ft_strsplit(pipes[i], ' '), env, pipes);
		exit(0);
	}
	else
		wait(NULL);
}

void			exec_cmd(char *line, t_env *env)
{
	char	**cmds;
	int		i;

	cmds = ft_strsplit(line, ';');
	i = 0;
	while (cmds[i])
	{
		exec_fork(cmds[i], env);
		i++;
	}
}

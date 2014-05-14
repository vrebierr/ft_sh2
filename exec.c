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
#include <sys/wait.h>

void	exec(t_cmd *cmd)
{
	pid_t	parent;

	parent = fork();
	if (parent > 0)
		wait(NULL);
	else if (parent == 0)
		execve(cmd->path, cmd->av, cmd->env->envp);
}

int		is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		builtin_exit();
	return (0);
}

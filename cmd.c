/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrebierr <vrebierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 15:36:09 by vrebierr          #+#    #+#             */
/*   Updated: 2014/05/14 15:36:10 by vrebierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh2.h"
#include <sys/stat.h>
#include <stdlib.h>

static char		*load_path(t_env *env, char *cmd)
{
	int			i;
	char		*tmp;
	char		*result;
	struct stat	buf;

	i = 0;
	result = NULL;
	while (env->paths[i] && result == NULL)
	{
		tmp = ft_strjoin(ft_strjoin(env->paths[i], "/"), cmd);
		if (stat(tmp, &buf) == 0)
			result = tmp;
		else
			i++;
		ft_strdel(&tmp);
	}
	if (result == NULL)
	{
		ft_putstr(cmd);
		ft_putstr(": command not found\n");
	}
	return (result);
}

static t_cmd	*add_cmd(t_cmd *list, char **av, t_env *env)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd != NULL)
	{
		cmd->env = env;
		cmd->cmd = av[0];
		cmd->av = av;
		cmd->next = NULL;
		cmd->path = load_path(env, cmd->cmd);
		if (list == NULL)
			list = cmd;
		else
		{
			tmp = list;
			while (tmp)
				tmp = tmp->next;
			tmp->next = cmd;
		}
	}
	return (list);
}

t_cmd			*init_cmd(char *line, t_env *env)
{
	t_cmd	*cmd;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_strsplit(line, ';');
	cmd = NULL;
	while (tmp[i])
	{
		add_cmd(cmd, ft_strsplit(tmp[i], ' '), env);
		i++;
	}
	free(tmp);
	tmp = NULL;
	return (cmd);
}

void			del_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		free(cmd->cmd);
		free(cmd->path);
		free(cmd->av);
		cmd->cmd = NULL;
		cmd->env = NULL;
		cmd->path = NULL;
		cmd->av = NULL;
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
		tmp = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrebierr <vrebierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 14:37:02 by vrebierr          #+#    #+#             */
/*   Updated: 2014/05/14 14:37:04 by vrebierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh2.h"
#include <stdlib.h>

int		main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;
	t_cmd	*cmd;

	(void)ac;
	(void)av;
	env = (t_env *)malloc(sizeof(t_env));
	env->envp = envp;
	env->paths = ft_strsplit(ft_strsplit(envp[0], '=')[1], ':');
	ft_putstr("$> ");
	while (get_next_line(0, &line))
	{
		cmd = init_cmd(line, env);
		exec(cmd);
		del_cmd(cmd);
		ft_putstr("$> ");
	}
	return (0);
}

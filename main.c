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

void	show_error(char *msg)
{
	ft_putendl(msg);
	exit(1);
}

t_env	*init_env(char **envp)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env != NULL)
	{
		env->envp = envp;
		env->paths = ft_strsplit(ft_strsplit(envp[0], '=')[1], ':');
	}
	return (env);
}

int		main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;
	int		ret;

	(void)ac;
	(void)av;
	env = init_env(envp);
	ret = 1;
	while (ret)
	{
		ft_putstr("$> ");
		if ((ret = get_next_line(0, &line)) == -1)
			break ;
		exec_cmd(line, env);
	}
	return (0);
}

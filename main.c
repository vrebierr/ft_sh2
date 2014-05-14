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

void	ft_exec(t_ctx *ctx)
{
	pid_t	parent;

	parent = fork();
	if (parent > 0)
		wait(NULL);
	else if (parent == 0)
		execve(ctx->path, ctx->argv, ctx->envp);
}

int		ft_is_builtin(t_ctx *ctx)
{
	if (ft_strcmp(ctx->cmd, "exit") == 0)
	{
		ft_exec_exit();
		return (1);
	}
	return (0);
}

void	ft_lauch(t_ctx *ctx)
{
	int			i;
	char		*tmp;
	struct stat	buf;

	i = 0;
	if (ft_is_builtin(ctx))
		return ;
	while (ctx->paths[i] && ctx->path == NULL)
	{
		tmp = ft_strjoin(ft_strjoin(ctx->paths[i], "/"), ctx->cmd);
		if (stat(tmp, &buf) == 0)
			ctx->path = tmp;
		else
			i++;
	}
	if (ctx->path == NULL)
	{
		ft_putstr(ctx->cmd);
		ft_putstr(": command not found\n");
	}
	else
		ft_exec(ctx);
}

void	ft_resetctx(t_ctx *ctx)
{
	free(ctx->argv);
	free(ctx->cmd);
	free(ctx->path);
	ctx->argv = NULL;
	ctx->cmd = NULL;
	ctx->path = NULL;
}


int		main(int ac, char **av, char **envp)
{
	int		ret;
	char	*line;
	t_ctx	*ctx;

	(void)ac;
	(void)av;
	ctx = (t_ctx *)malloc(sizeof(t_ctx));
	ctx->envp = envp;
	ctx->paths = ft_strsplit(ft_strsplit(envp[0], '=')[1], ':');
	ret = 1;
	while (ret)
	{
		ft_putstr("$> ");
		ret = get_next_line(1, &line);
		if (ret == -1)
			break ;
		ctx->argv = ft_strsplit(line, ' ');
		ctx->cmd = ctx->argv[0];
		ft_lauch(ctx);
		ft_resetctx(ctx);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrebierr <vrebierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 14:37:13 by vrebierr          #+#    #+#             */
/*   Updated: 2014/05/14 14:37:14 by vrebierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH2_H
# define FT_SH2_H
# include <libft.h>

typedef struct		s_env
{
	char			**paths;
	char			**envp;
}					t_env;

typedef struct		s_cmd
{
	char			*path;
	char			**av;
	char			*cmd;
	t_env			*env;
	struct s_cmd	*next;
}					t_cmd;

t_cmd				*init_cmd(char *line, t_env *env);
void				del_cmd(t_cmd *cmd);
void				builtin_exit(void);
void				exec(t_cmd *cmd);

#endif

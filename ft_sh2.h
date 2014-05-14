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
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct	s_ctx
{
	char		**argv;
	char		**envp;
	char		**paths;
	char		*path;
	char		*cmd;
}				t_ctx;

void	ft_exec_exit(void);

#endif

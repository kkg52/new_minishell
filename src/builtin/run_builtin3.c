/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgoc <kgoc@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:02:29 by kgoc              #+#    #+#             */
/*   Updated: 2023/10/09 17:03:56 by kgoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>

void	exec_pwd(t_parse *data)
{
	char	cwd[1024];	

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(data->outfile, &cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		g_shell->exec_status = 0;
	}
	else
	{
		perror("getcwd");
		g_shell->exec_status = 1;
	}
}

char	*get_home(void)
{
	t_list	*tmp;
	t_env	*env;

	tmp = g_shell->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "HOME"))
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}

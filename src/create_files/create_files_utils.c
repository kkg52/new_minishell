/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgoc <kgoc@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:02:35 by kgoc              #+#    #+#             */
/*   Updated: 2023/10/09 17:03:55 by kgoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	create_in_files_other(t_parse *data, char *pwd)
{
	if (pwd)
		free(pwd);
	printf("minishell: %s: No such file or directory\n", data->text[0]);
	return (0);
}

int	create_in_files(t_parse *data3, t_list *tmp3)
{
	t_parse	*data;
	char	str[256];	
	char	*pwd;
	char	*tmp;

	getcwd(str, 256);
	tmp = ft_strjoin(str, "/");
	tmp3 = tmp3->next;
	if (!tmp3)
		return (1);
	data = tmp3->content;
	pwd = ft_strjoin(tmp, data->text[0]);
	if (tmp)
		free(tmp);
	if (!access(pwd, F_OK))
	{
		if (data3->type == 5)
			data->fd = open(pwd, O_RDONLY, 0777);
	}
	else
		return (create_in_files_other(data, pwd));
	if (pwd)
		free(pwd);
	data3->infile = data->fd;
	return (1);
}

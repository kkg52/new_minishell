/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgoc <kgoc@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:03:02 by kgoc              #+#    #+#             */
/*   Updated: 2023/10/09 17:03:46 by kgoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	quote_len(char *data)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '\"' || data[i] == '\'')
			j++;
		i++;
	}
	return (j);
}

void	set_other_other(char *data, char *str, int *j, int i)
{
	int	tmp;

	tmp = *j;
	if (str && ((*str && str[i - 1] && str[i -2])
			&& (((str[i - 2] == '>' && str[i - 1] == '>')
					|| (str[i - 1] == '>' && str[i] != '>')) && str[i] != 2)))
	{
		data[tmp] = 2;
		*j += 1;
	}
	else if (str && ((str[i] == '<' && str[i + 1] == '<') || ((str[i] == '<'
					&& str[i - 1] != '<') && str[i - 1] != 2)))
	{
		data[tmp] = 2;
		*j += 1;
	}
	else if (str && ((str[i - 1] && str[i - 2]) && ((str[i - 2] == '<'
					&& str[i - 1] == '<') || ((str[i - 1] == '<'
						&& str[i] != '<') && str[i] != 2))))
	{
		data[tmp] = 2;
		*j += 1;
	}
}

void	set_other(char *data, char *str, int *j, int i)
{
	int	tmp;

	tmp = *j;
	if (i >= 1)
	{
		if (str && (((str[i] == '>' && str[i + 1] == '>') || (str[i] == '>'
						&& str[i - 1] != '>')) && str[i - 1] != 2))
		{
			data[tmp] = 2;
			*j += 1;
		}
		else if (str && (((str[i] == '|' && str[i - 1] != 2)
					|| (str[i - 1] == '|' && str[i] != 2))))
		{
			data[tmp] = 2;
			*j += 1;
		}
	}
	if (i >= 2)
		set_other_other(data, str, j, i);
}

char	*set_build(char *str)
{
	char	a;
	char	*data;
	int		j;
	int		i;

	i = 0;
	j = 0;
	data = malloc(sizeof(char) * (ft_strlen(str) * 2) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			a = str[i];
			data[j++] = str[i++];
			while (str[i] != a)
				data[j++] = str[i++];
		}
		else
			set_other(data, str, &j, i);
		data[j++] = str[i++];
	}
	data[j] = '\0';
	return (data);
}

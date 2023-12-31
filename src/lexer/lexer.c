/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgoc <kgoc@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:03:04 by kgoc              #+#    #+#             */
/*   Updated: 2023/10/09 17:03:39 by kgoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	cmd_build_other(int *i, int *len, char *cmd)
{
	int	a;
	int	tmp;
	int	size;

	tmp = *i;
	size = *len;
	a = cmd[tmp];
	while (size > 0)
	{
		if (cmd[tmp++] == a)
		{
			*i += 1;
			*len -= 1;
			size--;
			if (size % 2 == 0)
				return (1);
		}
	}
	return (0);
}

void	cmd_build_(char *cmd, int *len, int *i)
{
	int	tmp;
	int	a;
	int	j;

	j = *i;
	tmp = *len;
	a = cmd[j];
	while (tmp > 0)
	{
		if (cmd[j] == a)
		{
			*i += 1;
			j++;
			*len -= 1;
			tmp--;
			if (tmp % 2 == 0)
				break ;
		}
		*i += 1;
		j++;
	}
}

char	*cmd_build(char *cmd)
{
	int	len;
	int	i;
	int	size;

	i = 0;
	len = quote_len(cmd);
	size = ft_strlen(cmd);
	while (i < size)
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			cmd_build_(cmd, &len, &i);
		if (cmd[i++] == ' ')
			cmd[i - 1] = 2;
	}
	return (cmd);
}

char	*cmd_organize(char *cmd)
{
	char	c;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i++];
			while (cmd[i])
			{
				if (cmd[i] == c)
					break;
				i++;
			}
		}
		while (cmd[i] != 32 && cmd[i + 1])
			i++;
		if (cmd[i] == 32 && pos == 0)
			cmd[i] = 2;
		i++;
	}
	return (cmd);
}

void	lex_list(char *cmd, t_lexer **lex_table)
{
	char	**str;
	char	*str2;
	// char	*data;
	int		i;
	t_list	*new_node;

	i = 0;
	// data = cmd_build(cmd);
	// str2 = set_build(data);
	str2 = cmd_organize(cmd);
	str = ft_split(str2, 2);
	// free(str2);
	if (!str)
		return ;
	while (str[i])
	{
		new_node = ft_lstnew(str[i]);
		ft_lstadd_back(&(*lex_table)->lex, new_node);
		i++;
	}
	free(str);
}

// start point
void	lexer(void)
{
	lex_list(g_shell->cmd, &(g_shell->lex_list));
}

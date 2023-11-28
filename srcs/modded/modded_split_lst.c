/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modded_split_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:10:31 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/27 22:00:43 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	length_qoutes(char *s)
{
	int		i;
	char	qoutes;

	i = 0;
	if (s[0] == '\"')
		qoutes = '\"';
	if (s[0] == '\'')
		qoutes = '\'';
	i++;
	while (s[i] != '\0')
	{
		if (s[i] == qoutes)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	length_no_qoutes(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
			break ;
		i++;
	}
	return (i);
}

char	**parse_input_lst(char *input, int y)
{
	char	**command;
	int		i;
	int		size;

	command = (char **)ft_calloc(sizeof(char *), 1024);
	while (*input)
	{
		while (*input && *input == ' ')
			input++;
		if (!*input)
			break ;
		if (*input == '\"' || *input == '\'')
			input += length_qoutes(input);
		while (*input && *input == ' ')
			input++;
		size = length_no_qoutes(input);
		command[y] = ft_calloc(size + 1, sizeof(char));
		i = 0;
		while (i < size)
			command[y][i++] = *input++;
		command[y][i] = '\0';
		if (i != 0)
			y++;
	}
	return (command);
}

char	*connect(char *input)
{
	int		i;
	char	*res;
	char	**s;

	s = parse_input_lst(input, 0);
	res = ft_strdup("");
	i = 0;
	while (s[i] != NULL)
	{
		res = ft_strjoin_free(res, s[i]);
		i++;
	}
	free_2d_array(s);
	return (res);
}

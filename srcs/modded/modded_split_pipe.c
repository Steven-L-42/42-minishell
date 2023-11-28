/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modded_split_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:31:49 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/27 14:37:18 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_pipe_size(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += length_qoutes(s + i);
		else if (s[i] == '|')
			return (i);
		else
			i++;
	}
	return (i);
}

char	**get_pipe_split(char *input)
{
	char	**command;
	int		i;
	int		size;
	int		y;

	y = 0;
	command = (char **)ft_calloc(sizeof(char *), 1024);
	while (*input)
	{
		while (*input && *input == ' ')
			input++;
		while (*input && *input == '|')
			input++;
		if (!*input)
			break ;
		size = get_pipe_size(input);
		command[y] = ft_calloc(size + 1, sizeof(char));
		i = 0;
		while (i < size)
			command[y][i++] = *input++;
		command[y][i] = '\0';
		y++;
	}
	return (command);
}

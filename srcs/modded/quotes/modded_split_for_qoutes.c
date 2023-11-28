/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modded_split_for_qoutes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:13:27 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/27 22:00:48 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_sqoutes(char *input, int i)
{
	int	sqoutes;
	int	count;

	count = 0;
	sqoutes = 0;
	while (input[i] != '\0' && sqoutes != 2)
	{
		if (input[i] == '\'')
			sqoutes++;
		if (sqoutes != 0)
			count++;
		i++;
	}
	if (sqoutes == 2)
		return (count);
	else
		return (0);
}

char	**parse_input(char *input, int diff)
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
		if (!*input)
			break ;
		if (diff == 1)
			size = ft_strlenchar(input);
		else
			size = strlen_first_qoute(input);
		command[y] = ft_calloc(size + 1, sizeof(char));
		i = 0;
		while (i < size)
			command[y][i++] = *input++;
		command[y++][i] = '\0';
	}
	return (command);
}

char	*trim_and_conect(char **s)
{
	int		i;
	char	*res;

	res = ft_strdup("");
	i = 0;
	while (s[i] != NULL)
	{
		if (first_qoute(s[i]) == '\0')
			i++;
		if (s[i] == NULL)
			break ;
		s[i] = ft_strtrim_mod(s[i], first_qoute(s[i]));
		i++;
	}
	i = 0;
	while (s[i] != NULL)
	{
		res = ft_strjoin_free(res, s[i]);
		i++;
	}
	free_2d_array(s);
	return (res);
}

char	**der_grosse_bruder(char *cmd)
{
	char	**cmd_splitted;
	char	**temp;
	int		i;

	i = 0;
	cmd_splitted = parse_input(cmd, 1);
	while (cmd_splitted[i] != NULL)
	{
		temp = parse_input(cmd_splitted[i], 2);
		ft_free(cmd_splitted[i]);
		cmd_splitted[i] = trim_and_conect(temp);
		i++;
	}
	return (cmd_splitted);
}

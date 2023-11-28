/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:01:50 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 15:20:18 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strtrim_mod(char *s1, char c)
{
	size_t	start_length;
	int		count;

	count = 0;
	start_length = 0;
	while (s1[start_length])
	{
		while (s1[count] == c)
			count++;
		if (s1[count] != '\0')
			s1[start_length++] = s1[count++];
		else
			break ;
	}
	s1[start_length] = '\0';
	return (s1);
}

char	first_qoute(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			return ('\'');
		if (s[i] == '\"')
			return ('\"');
		i++;
	}
	return ('\0');
}

int	strlen_first_qoute(char *str)
{
	int		i;
	int		qoute;
	char	c;

	i = 0;
	qoute = 0;
	c = first_qoute(str);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			qoute++;
		if (qoute == 2)
			return (i + 1);
		i++;
	}
	return (i);
}

int	count_dqoutes(char *input, int i)
{
	int	dqoutes;
	int	count;

	count = 0;
	dqoutes = 0;
	while (input[i] != '\0' && dqoutes != 2)
	{
		if (input[i] == '\"')
			dqoutes++;
		if (dqoutes != 0)
			count++;
		i++;
	}
	if (dqoutes == 2)
		return (count);
	else
		return (0);
}

int	ft_strlenchar(char *input)
{
	int	i;

	i = 0;
	input = ft_strtrim(input, " ");
	while (input[i] != '\0' && input[0] != ' ')
	{
		if (input[i] == ' ')
			break ;
		else if (input[i] == '\"')
			i += count_dqoutes(input, i);
		else if (input[i] == '\'')
			i += count_sqoutes(input, i);
		else
			i++;
	}
	free(input);
	return (i);
}

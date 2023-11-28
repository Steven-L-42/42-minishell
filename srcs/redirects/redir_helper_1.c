/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:42:39 by slippert          #+#    #+#             */
/*   Updated: 2023/11/25 13:55:03 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_while_in_qoutes(char *cmd, char c, int i)
{
	int	count;

	count = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == c)
			return (count + 1);
		count++;
		i++;
	}
	return (count);
}

int	cut_string(char *str, int start, int end, char c)
{
	int		length;
	int		removal_length;
	char	*tmp_str;
	int		fd;

	length = strlen(str);
	removal_length = end - start + 1;
	tmp_str = ft_substr(str, start, end - start);
	if (c == '>')
		tmp_str = ft_strtrim_free(tmp_str, " >\'\"");
	tmp_str = ft_strtrim_free(tmp_str, "\"\'");
	fd = open(tmp_str, O_WRONLY | O_CREAT | O_TRUNC, 0700);
	if (check_perm_or_file_2(fd, tmp_str))
		return (close(fd), free(tmp_str), 1);
	close(fd);
	free(tmp_str);
	ft_memmove(str + start, str + end + 1, length - end);
	length -= removal_length;
	str[length + 1] = '\0';
	return (0);
}

int	first_redir(char *cmd, char c)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == c)
			return (i);
		if (cmd[i] == '\"')
			i += count_while_in_qoutes(cmd, '\"', i + 1);
		if (cmd[i] == '\'')
			i += count_while_in_qoutes(cmd, '\'', i + 1);
		i++;
	}
	return (-1);
}

int	cut_string_appendend(char *str, int start, int end, char c)
{
	int		length;
	int		removal_length;
	char	*temp;
	int		fd;

	length = strlen(str);
	removal_length = end - start + 1;
	temp = ft_substr(str, start, end - start);
	if (c == '>')
		temp = ft_strtrim_free(temp, " >\'\"");
	temp = ft_strtrim_free(temp, "\"\'");
	fd = open(temp, O_WRONLY | O_CREAT, 0700);
	if (check_perm_or_file_2(fd, temp))
		return (close(fd), free(temp), 1);
	close(fd);
	free(temp);
	ft_memmove(str + start, str + end + 1, length - end);
	length -= removal_length;
	str[length + 1] = '\0';
	return (0);
}

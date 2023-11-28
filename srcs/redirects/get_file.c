/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:58:15 by slippert          #+#    #+#             */
/*   Updated: 2023/11/25 13:51:31 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_file_helper(char *str, char c, int append)
{
	int	file;

	str = ft_strtrim_free(str, "\"\'");
	if (c == '>' && append == 0)
	{
		file = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (check_perm_or_file_1(file, str))
			return (-1);
	}
	if (c == '<' && append == 0)
		file = open(str, O_RDONLY);
	if (append == 1)
	{
		file = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (check_perm_or_file_1(file, str))
			return (-1);
	}
	free(str);
	return (file);
}

int	get_file(char *cmd, char c)
{
	char	*str;
	int		i;
	int		append;

	append = 0;
	str = is_last_redir(cmd, c, 0, 0);
	if (str[0] == '>' && str[1] == '>')
		append = 1;
	if (c == '>')
		str = ft_strtrim(str, " >");
	if (c == '<')
		str = ft_strtrim(str, " <");
	i = 0;
	if (str[i] == '\"')
		i += count_while_in_qoutes(str, '\"', i + 1);
	if (str[i] == '\'')
		i += count_while_in_qoutes(str, '\'', i + 1);
	i--;
	while (str[++i] != '\0')
		if (str[i] == ' ' || str[i] == c)
			break ;
	str = ft_substr_free(str, 0, i);
	return (get_file_helper(str, c, append));
}

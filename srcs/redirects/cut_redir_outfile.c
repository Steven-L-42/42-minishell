/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_redir_outfile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:57:42 by slippert          #+#    #+#             */
/*   Updated: 2023/11/24 19:09:04 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cut_redir_helper_2(char *cmd, int *end)
{
	while (cmd[++(*end)] != '\0')
	{
		if (cmd[*end] == ' ' || cmd[*end] == '>' || cmd[*end] == '|'
			|| cmd[*end] == '<')
			break ;
		if (cmd[*end] == '\"')
			*end += count_while_in_qoutes(cmd, '\"', *end + 1);
		if (cmd[*end] == '\'')
			*end += count_while_in_qoutes(cmd, '\'', *end + 1);
	}
}

static void
	cut_redir_helper_1(char *cmd, int start, int *end, int *appendent_redir)
{
	if (cmd[start] == '>' && cmd[start + 1] == '>')
	{
		(*end)++;
		*appendent_redir = 1;
	}
	while (cmd[*end] == ' ')
		(*end)++;
	(*end)--;
	cut_redir_helper_2(cmd, end);
}

int	cut_redir_outfile(char *cmd, char c)
{
	int	start;
	int	end;
	int	appendent_redir;

	start = 0;
	end = 0;
	appendent_redir = 0;
	start = first_redir(cmd, c);
	end = start;
	end++;
	cut_redir_helper_1(cmd, start, &end, &appendent_redir);
	if (c == '>' && appendent_redir != 1)
		if (cut_string(cmd, start, end, c) == 1)
			return (1);
	if (c == '>' && appendent_redir == 1)
		if (cut_string_appendend(cmd, start, end, c) == 1)
			return (1);
	if (c == '<' && appendent_redir != 1)
		if (cut_string_infile(cmd, start, end, c) == 1)
			return (1);
	return (0);
}

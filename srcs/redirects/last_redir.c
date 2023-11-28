/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 11:26:34 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/27 17:32:54 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*is_last_redir(char *cmd, char c, int i, int check)
{
	int		temp;
	int		append;

	append = 10241024;
	temp = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			i += count_while_in_qoutes(cmd, cmd[i], i);
		if (cmd[i] == '\0')
			break ;
		if (cmd[i] == c)
		{
			append = i;
			if (i != 0 && cmd[i - 1] == c)
				check = 1;
			else
				check = 0;
		}
		i++;
	}
	if (check == 0)
		return (cmd += append);
	else
		return (cmd += append - 1);
}

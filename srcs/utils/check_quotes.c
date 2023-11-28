/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:57:53 by slippert          #+#    #+#             */
/*   Updated: 2023/11/23 12:00:08 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	single_check_helper(t_shell *sh, int *i)
{
	if (sh->input[*i] && sh->input[*i] == '\'')
	{
		(*i)++;
		while (sh->input[*i] && sh->input[*i] != '\'')
		{
			sh->has_single_quote++;
			(*i)++;
		}
		if (sh->input[*i] != '\'')
			return (ft_putendl_fd("Quotes not closed", 2), false);
	}
	return (true);
}

static bool	double_check_helper(t_shell *sh, int *i)
{
	if (sh->input[*i] && sh->input[*i] == '\"')
	{
		(*i)++;
		while (sh->input[*i] && sh->input[*i] != '\"')
			(*i)++;
		if (sh->input[*i] != '"')
			return (ft_putendl_fd("Quotes not closed", 2), false);
	}
	return (true);
}

bool	quote_check(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->input[i])
	{
		if (!single_check_helper(sh, &i))
			return (false);
		if (!double_check_helper(sh, &i))
			return (false);
		i++;
	}
	return (true);
}

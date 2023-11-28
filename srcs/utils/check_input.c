/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanger <jsanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:41:25 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/23 21:43:46 by jsanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_input(t_shell *sh, char *input)
{
	int		i;

	sh->tokens = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|')
			sh->tokens++;
		i++;
	}
	free(input);
}

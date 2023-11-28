/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:51:48 by slippert          #+#    #+#             */
/*   Updated: 2023/11/25 14:11:31 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	own_export(t_shell *sh, char **command, int is_allocated)
{
	int	i;

	i = 1;
	sh->is_builtin = 1;
	if (command[i])
	{
		while (command[i])
		{
			if (!ft_valid_identifier(command[i++], "\'\"$`\\-+|&;()<>*?[]{}!,"))
			{
				sh->exitcode = 1;
				ft_putstr_fd("export: ", 2);
				ft_putstr_fd(command[i - 1], 2);
				ft_putendl_fd(": not a valid identifier", 2);
				return ;
			}
		}
		i = 1;
		while (command[i])
			own_export_helper(sh, command[i++], is_allocated);
		return ;
	}
	i = 0;
	while (sh->env[i])
		ft_printf("declare -x %s\n", sh->env[i++]);
}

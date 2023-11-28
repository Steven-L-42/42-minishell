/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:53:13 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 18:02:53 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	own_env(t_shell *sh)
{
	int	i;

	i = 1;
	sh->is_builtin = 1;
	i = 0;
	while (sh->env[i])
		ft_printf("%s\n", sh->env[i++]);
}

void	own_unset(t_shell *sh, char **command)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	sh->is_builtin = 1;
	while (command[i])
	{
		j = -1;
		while (sh->env[++j])
		{
			len = ft_strlen_until_c(command[i], '=');
			if (!ft_strncmp(sh->env[j], command[i], len) && j--)
			{
				while (sh->env && sh->env[++j - 1])
				{
					ft_free(sh->env[j]);
					sh->env[j] = sh->env[j + 1];
				}
				sh->exitcode = 0;
				break ;
			}
		}
		i++;
	}
}

void	own_pwd(t_shell *sh)
{
	char	cwd[256];

	sh->is_builtin = 1;
	getcwd(cwd, sizeof(cwd));
	ft_putendl_fd(cwd, 1);
}

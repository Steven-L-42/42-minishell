/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:54:17 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 17:38:13 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	echo_helper(t_shell *sh, char **command, int *i)
{
	int		pid;
	char	**new;

	if (ft_strcontain(command[*i]) > 0)
	{
		new = split_including(command[*i], '$');
		own_echo(sh, new, 1);
		return ;
	}
	else if (!ft_strcmp(command[*i], "$"))
		ft_printf("%s", command[*i++]);
	else if (command[*i][0] == '$' && ft_strcmp(command[*i], "$HOSTNAME"))
		own_dollar(sh, command[*i]);
	else if (command[*i][0] != '$')
		ft_printf("%s", command[*i]);
	else
	{
		pid = fork();
		if (pid == 0)
			exec(sh, command[*i] + 1);
		if (pid != 0)
			waitpid(pid, NULL, 0);
	}
}

static void	echo_nl(char **command, int *i, int *no_nl)
{
	if (!ft_strncmp(command[*i], "-n\0", 3))
	{
		*no_nl = 1;
		*i += 1;
	}
}

void	own_echo(t_shell *sh, char **command, int is_splitted)
{
	int		i;
	int		no_nl;

	i = 1;
	no_nl = 0;
	if (!command[i])
		ft_printf("\n");
	else
	{
		echo_nl(command, &i, &no_nl);
		while (command[i])
		{
			echo_helper(sh, command, &i);
			i++;
			if (command[i] && !is_splitted && !no_nl)
				ft_printf(" ");
		}
		if (!no_nl)
			ft_printf("\n");
	}
	sh->is_builtin = 1;
}

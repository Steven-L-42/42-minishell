/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:42:41 by slippert          #+#    #+#             */
/*   Updated: 2023/11/24 18:52:45 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_shell *sh, char **command)
{
	sh->is_builtin = 1;
	if (!command[2] && command[1] && !ft_is_string(command[1]))
		sh->exitcode = (unsigned char)ft_atoi(command[1]);
	else if (command[1] && !command[2])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(command[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		sh->exitcode = 255;
	}
	else if (command[2])
	{
		ft_putstr_fd("exit: ", 2);
		ft_putendl_fd("too many arguments", 2);
		sh->exitcode = 1;
		return ;
	}
	sh->is_running = 0;
}
// exit(sh->exitcode);

void	check_builtins(t_shell *sh, char **command)
{
	if (!ft_strcmp(command[0], "echo") && command[1]
		&& !ft_strncmp(command[1], "<<", 2))
		return ;
	if (!ft_strcmp(command[0], "exit"))
		ft_exit(sh, command);
	else if (!ft_strcmp(command[0], "export"))
		own_export(sh, command, 0);
	else if (!ft_strcmp(command[0], "unset"))
		own_unset(sh, command);
	else if (!ft_strcmp(command[0], "cd"))
		own_cd(sh);
	else if (!ft_strcmp(command[0], "pwd"))
		own_pwd(sh);
	else if (!ft_strcmp(command[0], "env"))
		own_env(sh);
	else if (!sh->has_single_quote && !ft_strcmp(command[0], "echo"))
		own_echo(sh, command, 0);
}

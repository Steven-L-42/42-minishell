/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:25:39 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/27 14:37:12 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_file_dir(t_shell *sh, char *cmd)
{
	sh->exitcode = 127;
	if (!ft_strncmp(cmd, "./", 2))
	{
		if (ft_boolstrchr(cmd + 2, '.'))
			ft_putendl_fd(": No such file or directory", 2);
		else if (sh->exitcode--)
		{
			if (access(cmd, F_OK | X_OK) == -1)
				ft_putendl_fd(": Permission denied", 2);
			else
				ft_putendl_fd(": is a directory", 2);
		}
	}
	else if (!ft_strncmp(cmd, "/", 1))
	{
		if (!ft_boolstrchr(cmd + 1, '/'))
			ft_putendl_fd(": No such file or directory", 2);
		else if (sh->exitcode--)
			ft_putendl_fd(": is a directory", 2);
	}
	else
		ft_putendl_fd(": command not found", 2);
}

char	*search_in_env(t_shell *sh, char *cmd)
{
	int		i;
	int		len;
	char	*temp;

	if (!ft_strncmp(cmd, "$?", 2) || !cmd[1])
		return (cmd);
	i = -1;
	while (sh->env[++i])
	{
		if (!ft_strncmp(sh->env[i], cmd + 1, ft_strlen_until_c(sh->env[i],
					'=')))
		{
			len = ft_strlen_until_c(sh->env[i], '=');
			temp = ft_substr(sh->env[i] + 1, len, 1024);
			return (temp);
		}
	}
	return (NULL);
}

void	exec_helper(t_shell *sh, char **s_cmd, char *cmd)
{
	char	*path;

	path = get_path(s_cmd[0], sh->env);
	sh->exitcode = 0;
	if (!ft_strncmp(cmd, "$", 1))
		s_cmd[0] = search_in_env(sh, s_cmd[0]);
	if (s_cmd[0] && execve(path, s_cmd, sh->env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s_cmd[0], 2);
		check_file_dir(sh, s_cmd[0]);
	}
}

void	exec(t_shell *sh, char *cmd)
{
	char	**s_cmd;

	s_cmd = der_grosse_bruder(cmd);
	if (!sh->is_heredoc)
		check_builtins(sh, s_cmd);
	if (sh->is_builtin)
	{
		free_2d_array(s_cmd);
		exit(sh->exitcode);
	}
	if (!sh->is_builtin)
		exec_helper(sh, s_cmd, cmd);
	free_2d_array(s_cmd);
	sh->is_builtin = 0;
	exit(sh->exitcode);
}

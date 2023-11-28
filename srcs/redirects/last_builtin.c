/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:38:42 by slippert          #+#    #+#             */
/*   Updated: 2023/11/24 14:21:41 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	is_last_builtin_3(t_shell *sh, char **command, int i)
{
	if (first_redir(command[i], '>') != -1)
	{
		redir_out(sh, command[i]);
		close(sh->stdout_saved);
		if (sh->exitcode == 1)
			exit(sh->exitcode);
		dup2(sh->outfile, STDOUT);
		close(sh->outfile);
	}
	if (first_redir(command[i], '<') != -1)
	{
		redir_in(sh, command[i]);
		close(sh->stdin_saved);
		if (sh->exitcode == 1)
			exit(sh->exitcode);
		dup2(sh->infile, STDIN);
		close(sh->infile);
	}
}

static void	is_last_builtin_2(t_shell *sh, char **command, int i)
{
	int	pid;
	int	status;

	if (sh->pipe_builtin)
	{
		pid = fork();
		if (pid == 0)
		{
			is_last_builtin_3(sh, command, i);
			exec(sh, command[i]);
		}
		if (pid != 0)
			waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			sh->exitcode = WEXITSTATUS(status);
	}
}

int	is_last_builtin_1(t_shell *sh, char **command)
{
	int	i;

	i = 0;
	while (command[i + 1])
		i++;
	command[i] = ft_strtrim_free(command[i], " ");
	if (!ft_strncmp(command[i], "exit", 4))
		sh->pipe_builtin = 1;
	else if (!ft_strncmp(command[i], "export", 6))
		sh->pipe_builtin = 1;
	else if (!ft_strncmp(command[i], "unset", 5))
		sh->pipe_builtin = 1;
	else if (!ft_strncmp(command[i], "cd", 2))
		return (1);
	else if (!ft_strncmp(command[i], "pwd", 3))
		sh->pipe_builtin = 1;
	else if (!ft_strncmp(command[i], "env", 3))
		sh->pipe_builtin = 1;
	else if (ft_strnstr(command[i], "echo", strlen(command[i])))
		sh->pipe_builtin = 1;
	else
		sh->pipe_builtin = 0;
	is_last_builtin_2(sh, command, i);
	return (sh->pipe_builtin);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:18:02 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 14:43:41 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_fd(t_shell *sh)
{
	if (sh->outfile)
	{
		dup2(sh->stdout_saved, STDOUT);
		close(sh->stdout_saved);
		sh->outfile = 0;
	}
	if (sh->infile)
	{
		dup2(sh->stdin_saved, STDIN);
		close(sh->stdin_saved);
		sh->infile = 0;
	}
}

int	redir_out_helper(t_shell *sh, char *cmd)
{
	while (first_redir(cmd, '>') != -1)
	{
		if (cut_redir_outfile(cmd, '>') == 1)
		{
			sh->exitcode = 1;
			return (0);
		}
	}
	return (1);
}

void	redir_out(t_shell *sh, char *cmd)
{
	char	*temp;

	temp = ft_strdup(cmd);
	while (first_redir(temp, '>') != -1)
	{
		if (cut_redir_outfile(temp, '>') == 1)
		{
			sh->exitcode = 1;
			free(temp);
			return ;
		}
	}
	free(temp);
	sh->stdout_saved = dup(STDOUT);
	sh->outfile = get_file(cmd, '>');
	if (sh->outfile == -1)
	{
		sh->exitcode = 1;
		return ;
	}
	if (!redir_out_helper(sh, cmd))
		return ;
	dup2(sh->outfile, STDOUT);
}

void	redir_in(t_shell *sh, char *cmd)
{
	char	*temp;

	temp = ft_strdup(cmd);
	while (first_redir(temp, '<') != -1)
	{
		if (cut_redir_outfile(temp, '<') == 1)
		{
			sh->exitcode = 1;
			free(temp);
			return ;
		}
	}
	free(temp);
	sh->stdin_saved = dup(STDIN);
	sh->infile = get_file(cmd, '<');
	while (first_redir(cmd, '<') != -1)
	{
		if (cut_redir_outfile(cmd, '<') == 1)
		{
			sh->exitcode = 1;
			return ;
		}
	}
	dup2(sh->infile, STDIN);
}

bool	redir_test(t_shell *sh)
{
	if (first_redir(sh->input, '>') != -1)
	{
		redir_out(sh, sh->input);
		if (sh->exitcode == 1)
		{
			reset_fd(sh);
			return (1);
		}
		dup2(sh->outfile, STDOUT);
		close(sh->outfile);
	}
	if (first_redir(sh->input, '<') != -1)
	{
		redir_in(sh, sh->input);
		if (sh->exitcode == 1)
		{
			reset_fd(sh);
			return (1);
		}
		dup2(sh->infile, STDIN);
		close(sh->infile);
	}
	return (0);
}

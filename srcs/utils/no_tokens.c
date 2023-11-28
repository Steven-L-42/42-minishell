/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:41:16 by slippert          #+#    #+#             */
/*   Updated: 2023/11/28 19:37:31 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	buildin_test(t_shell *sh)
{
	int	pid;
	int	status;

	if (!sh->is_builtin)
	{
		pid = fork();
		if (pid == 0)
			exec(sh, sh->input);
		if (pid != 0)
			waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			sh->exitcode = WEXITSTATUS(status);
	}
}

void	byte_read(t_shell *sh)
{
	int		bytes;
	char	c;

	bytes = 1;
	while (bytes)
	{
		bytes = read(sh->heredoc_fd, &c, 1);
		if (bytes <= 0)
			break ;
		write(1, &c, 1);
	}
}

void	ft_no_tokens(t_shell *sh)
{
	char	**s_cmd;

	heredoc(sh);
	if (sh->input && sh->input[0] && redir_test(sh))
		return ;
	if (sh->is_heredoc && sh->input)
	{
		sh->heredoc_fd = open(HERE_PATH, O_RDONLY);
		if (sh->is_cat)
			byte_read(sh);
		close(sh->heredoc_fd);
		unlink(HERE_PATH);
	}
	else if (sh->input && sh->input[0])
	{
		s_cmd = der_grosse_bruder(sh->input);
		check_builtins(sh, s_cmd);
		free_2d_array(s_cmd);
	}
	if (sh->input && sh->input[0])
		buildin_test(sh);
	sh->is_builtin = 0;
	reset_fd(sh);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:13:18 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 21:53:48 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_variables(t_shell *sh)
{
	sh->is_running = 1;
	sh->tokens = 0;
	sh->has_single_quote = 0;
	sh->heredoc_fd = 0;
	sh->is_heredoc = 0;
	sh->heredoc_ok = 0;
	sh->is_builtin = 0;
	sh->is_pipe = 0;
	sh->pipe_builtin = 0;
	sh->exitcode = 0;
	sh->stdout_saved = 0;
	sh->stdin_saved = 0;
	sh->outfile = 0;
	sh->infile = 0;
	sh->is_cat = 0;
}

void	init(t_shell *sh, int argc, char **argv, char **env)
{
	int	i;

	if (argv)
	{
		if (argc > 1)
		{
			ft_putendl_fd("Too many arguments!", 2);
			sh->exitcode = 1;
			exit(sh->exitcode);
		}
		sh->env = get_env(env);
	}
	sh->usr_path = ft_strnstr(sh->env[5], "/", 1024);
	i = -1;
	while (sh->env[++i])
		if (ft_strnstr(sh->env[i], "PWD", 3))
			break ;
	sh->own_path = ft_strnstr(sh->env[i], "/", 1024);
	init_variables(sh);
}

void	reset_vars(t_shell *sh)
{
	ft_free(sh->input);
	ft_free(sh->shell_name);
	sh->pipe_builtin = 0;
	sh->has_single_quote = 0;
	sh->is_heredoc = 0;
}

int	read_input(t_shell *sh)
{
	if (!sh->input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		return (reset_vars(sh), 0);
	}
	else if (sh->input && *sh->input && quote_check(sh))
	{
		sh->input = ft_strtrim_free(sh->input, " \t");
		if (sh->input && sh->input[0] && ft_strncmp(sh->input, "\n", 1))
		{
			add_history(sh->input);
			check_input(sh, connect(sh->input));
			if (sh->tokens == 0)
				ft_no_tokens(sh);
			else
				check_if_only_pipe(sh);
		}
		else
			ft_free(sh->input);
	}
	return (reset_vars(sh), 1);
}

int	loop(t_shell *sh)
{
	while (sh->is_running)
	{
		sh->input = readline(set_pathname(sh));
		if (!read_input(sh))
			return (sh->exitcode);
	}
	return (sh->exitcode);
}

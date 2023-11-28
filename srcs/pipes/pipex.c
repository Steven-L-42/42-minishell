/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:28:57 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/27 21:25:04 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_outfiles(char **command)
{
	int	i;

	i = 0;
	if (command[0] == NULL)
		return ;
	while (command[i + 1])
	{
		while (first_redir(command[i], '>') != -1)
		{
			if (cut_redir_outfile(command[i], '>') == 1)
				return ;
		}
		while (first_redir(command[i], '<') != -1)
		{
			if (cut_redir_outfile(command[i], '<') == 1)
				return ;
		}
		i++;
	}
}

void	make_children_helper(t_shell *sh, char *cmd, int pipefd[2])
{
	if (first_redir(cmd, '<') != -1)
	{
		redir_in(sh, cmd);
		close(sh->stdin_saved);
		if (sh->exitcode == 1)
			exit(sh->exitcode);
		dup2(sh->infile, STDIN);
		close(sh->infile);
	}
	if (first_redir(cmd, '>') != -1)
	{
		redir_out(sh, cmd);
		close(sh->stdout_saved);
		if (sh->exitcode == 1)
		{
			close(sh->stdout_saved);
			exit(sh->exitcode);
		}
		dup2(sh->outfile, STDOUT);
		close(sh->outfile);
	}
	else
		dup2(pipefd[1], STDOUT);
}

void	make_children(t_shell *sh, char *cmd)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
	}
	else
	{
		make_children_helper(sh, cmd, pipefd);
		close(pipefd[0]);
		exec(sh, cmd);
	}
}

static void	pipex_helper(int *i, int ac, char **av, t_shell *sh)
{
	make_children(sh, av[0]);
	while (*i < ac - 1)
		make_children(sh, av[(*i)++]);
	sh->is_pipe = 1;
	if (first_redir(av[*i], '>') != -1)
	{
		redir_out(sh, av[*i]);
		dup2(sh->outfile, STDOUT);
		close(sh->outfile);
	}
	if (first_redir(av[*i], '<') != -1)
	{
		redir_in(sh, av[*i]);
		if (sh->exitcode == 1)
			exit(sh->exitcode);
		dup2(sh->infile, STDIN);
		close(sh->infile);
	}
}

void	pipex(int ac, char **av, t_shell *sh)
{
	int	i;
	int	pid;
	int	status;

	i = 1;
	if (is_last_builtin_1(sh, av))
	{
		create_outfiles(av);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (ac >= 2)
		{
			pipex_helper(&i, ac, av, sh);
			exec(sh, av[i]);
		}
		else
			write(STDERR, "Invalid number of arguments.\n", 29);
	}
	sh->is_builtin = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->exitcode = WEXITSTATUS(status);
}

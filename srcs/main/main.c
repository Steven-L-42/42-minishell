/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:14:26 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 21:54:50 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_free(char *str)
{
	if (str && str[0])
	{
		free(str);
		str = NULL;
	}
}

void	ft_free_all(t_shell *sh)
{
	free_2d_array(sh->env);
	free(sh);
}

int	main(int argc, char **argv, char **env)
{
	t_shell				*sh;
	struct sigaction	sa;
	int					exit;

	sh = (t_shell *)malloc(sizeof(t_shell));
	sa.sa_handler = handle_signal;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	init(sh, argc, argv, env);
	exit = loop(sh);
	ft_free_all(sh);
	return (exit);
}

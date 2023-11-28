/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:15:30 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 21:19:36 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void
	heredoc_line(t_shell *sh, char *delim)
{
	char	*line;
	char	*str;

	str = ft_calloc(1, 1);
	while (1)
	{
		line = readline("heredoc > ");
		if (!ft_strcmp(line, delim))
			break ;
		str = ft_strjoin_nl(str, line);
		ft_free(line);
	}
	write(sh->heredoc_fd, str, ft_strlen(str));
	ft_free(line);
	ft_free(str);
}

static void	update_input(t_shell *sh, char *second, char *third)
{
	char	*temp;

	if (!ft_strcmp(third, ">") || !ft_strcmp(third, "<"))
		third = second;
	temp = sh->input;
	free(sh->input);
	sh->input = ft_strnstr(temp, third, ft_strlen(temp));
	sh->input = ft_substr(sh->input, ft_strlen(third), ft_strlen(sh->input));
	if (!*sh->input)
		free(sh->input);
}

static char	*get_delim(char **command, int deli_pos)
{
	char	*delim;

	delim = ft_substr(command[1 - deli_pos], 2, ft_strlen(command[1
				- deli_pos]));
	if (delim && !delim[0])
	{
		free(delim);
		delim = command[2 - deli_pos];
	}
	return (delim);
}

static void	ft_helper(t_shell *sh, char **command, char *delim, int action_pos)
{
	heredoc_line(sh, delim);
	close(sh->heredoc_fd);
	if (ft_strcmp(command[action_pos], "cat"))
	{
		sh->is_cat = 0;
		free(sh->input);
		sh->input = ft_strjoin(command[action_pos], " ");
	}
	else if (++sh->is_cat)
		update_input(sh, command[1], command[2]);
}

// || (command && ft_strnstr_bool(command[0], "<<", ft_strlen(command[0]))))
void	heredoc(t_shell *sh)
{
	char	**command;
	char	*delim;
	int		deli_pos;
	int		action_pos;

	command = der_grosse_bruder(sh->input);
	command = kleiner_zwilling(command);
	if ((command && command[1] && (!ft_strncmp(command[0], "<<", 2)
				|| !ft_strncmp(command[1], "<<", 2))))
	{
		deli_pos = 0;
		action_pos = 0;
		if (!ft_strncmp(command[0], "<<", 2))
		{
			deli_pos = 1;
			action_pos = 2;
		}
		delim = get_delim(command, deli_pos);
		sh->is_heredoc = 1;
		sh->heredoc_fd = open(HERE_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
		if (sh->heredoc_fd)
			ft_helper(sh, command, delim, action_pos);
	}
	if (command)
		free_2d_array(command);
}

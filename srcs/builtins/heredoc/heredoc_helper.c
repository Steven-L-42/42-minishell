/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:07:14 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 21:08:16 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	process_command(char **command, char ***new, int *y, int y2)
{
	int	x;

	if (!ft_strncmp(command[y2], "<<", 2) && ft_strcmp(command[y2], "<<"))
	{
		(*new)[*y] = ft_substr(command[y2], 0, 2);
		(*new)[++(*y)] = ft_substr(command[y2], 2, ft_strlen(command[y2]));
	}
	else if (ft_strnstr_bool(command[y2], "<<", ft_strlen(command[y2]))
		&& ft_strcmp(command[y2], "<<"))
	{
		x = 0;
		while (command[y2][x] && command[y2][x] != '<')
			x++;
		(*new)[*y] = ft_substr(command[y2], 0, x);
		(*new)[++(*y)] = ft_substr(command[y2], x, 2);
		if (command[y2][x + 3])
			(*new)[++(*y)] = ft_substr(command[y2], x + 2,
					ft_strlen(command[y2]));
	}
	else
		(*new)[(*y)] = ft_strdup(command[y2]);
}

char	**kleiner_zwilling(char **command)
{
	char	**new;
	int		y;
	int		y2;

	y = 0;
	y2 = 0;
	new = ft_calloc(1024, sizeof(char *));
	if (!new)
		return (command);
	while (command && command[y2])
	{
		process_command(command, &new, &y, y2);
		y2++;
		y++;
	}
	free_2d_array(command);
	return (new);
}
// for (size_t i = 0; new[i]; i++)
// {
// 	printf("%s\n", new[i]);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_echo_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:10:36 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 18:41:14 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_strcontain(char *command)
{
	int	i;

	i = 0;
	while (command[i] && command[i + 1])
	{
		if (command[i] == '$' && command[i + 1] != ' ')
			return (i);
		i++;
	}
	return (0);
}

int	ft_strcontainchar(char *command, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 2;
	while (command[i] && command[i + 1])
	{
		if (command[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	**split_including(char *command, char c)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	new = ft_calloc(1024, sizeof(char *));
	j = 1;
	i = 0;
	k = 0;
	while (command[i])
	{
		k = 0;
		new[j] = ft_calloc(1024, sizeof(char));
		while (command[i] && command[i] != c)
			new[j][k++] = command[i++];
		k = 0;
		j++;
		new[j] = ft_calloc(1024, sizeof(char));
		while (command[i] && command[i] != ' ')
			new[j][k++] = command[i++];
		j++;
	}
	return (new);
}

void	own_dollar(t_shell *sh, char *command)
{
	int		j;
	char	*temp;

	if (command[1] == '?')
	{
		temp = ft_itoa(sh->exitcode);
		ft_printf("%s%s", temp, command + 2);
		free(temp);
	}
	else if (command[2] && command[2] != ' ')
	{
		j = -1;
		command = ft_strjoin(command + 1, "=");
		while (sh->env[++j])
			if (ft_strnstr(sh->env[j], command, ft_strlen(command)))
				break ;
		if (sh->env[j])
		{
			temp = ft_strnstr(sh->env[j], "=", ft_strlen(command));
			ft_printf("%s", ++temp);
		}
		free(command);
	}
}

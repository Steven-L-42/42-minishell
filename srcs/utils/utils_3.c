/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:53:39 by slippert          #+#    #+#             */
/*   Updated: 2023/11/23 13:43:52 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_last_pathname(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	len = ft_strlen(str) - 1;
	while (len)
	{
		if (str[len] == '/')
			break ;
		len--;
		i++;
	}
	new = ft_calloc(i + 1, sizeof(char));
	len++;
	while (str[len])
		new[j++] = str[len++];
	return (new);
}

char	*ft_remove_until(char *str, char c, int times)
{
	int		len;
	int		j;
	char	*new;

	len = ft_strlen(str) - 1;
	while (len)
	{
		len--;
		if (str[len] == c)
		{
			times--;
			if (times <= 0)
				break ;
		}
	}
	len--;
	new = ft_calloc(len + 1, sizeof(char));
	j = -1;
	while (j++ < len)
		new[j] = str[j];
	return (new);
}

const char	*set_pathname(t_shell *sh)
{
	const char	name_end[10] = " ➤ \033[0m";
	const char	name_w_path[22] = "\033[1m\033[32mminishell ~/";
	const char	name_o_path[19] = "\033[1m\033[32mminishell";
	char		*new_path;
	char		*temp_path;

	getcwd(sh->cur_path, sizeof(sh->cur_path));
	new_path = get_last_pathname(sh->cur_path);
	if (ft_strcmp(sh->cur_path, sh->own_path))
		temp_path = ft_strjoin(name_w_path, new_path);
	else
		temp_path = ft_strjoin(name_o_path, "");
	sh->shell_name = ft_strjoin(temp_path, name_end);
	free(temp_path);
	free(new_path);
	return (sh->shell_name);
}
// PS1="\033[1m\033[32mminishell ➤ \033[0m"

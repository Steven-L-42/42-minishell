/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:54:53 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/27 16:56:25 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_env(char **env_stack)
{
	int		i;
	int		array_len;
	char	**env;

	i = 0;
	array_len = array_2d_len(env_stack);
	env = ft_calloc(sizeof(char *), 1024);
	if (env == NULL)
		return (NULL);
	while (env_stack && env_stack[i])
	{
		env[i] = ft_strdup(env_stack[i]);
		i++;
	}
	return (env);
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

int	array_2d_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	*ft_strjoin_nl(char *old, char *line)
{
	int		i;
	int		j;
	char	*new;

	new = ft_calloc(ft_strlen(old) + ft_strlen(line) + 10, 1);
	i = -1;
	while (old[++i])
		new[i] = old[i];
	j = 0;
	while (line[j])
		new[i++] = line[j++];
	new[i++] = '\n';
	free(old);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 14:10:39 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 16:47:42 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_valid_identifier(char *command, char *set)
{
	int	i;
	int	j;

	i = 0;
	if (ft_isdigit(command[i]) || command[i] == '=')
		return (0);
	while (command[i])
	{
		j = 0;
		while (set[j])
		{
			if (command[i] == set[j])
				return (0);
			j++;
		}
		i++;
		if (command[i] == '=')
			return (1);
	}
	return (1);
}

int	ft_strlen_until_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

static int	ft_haschar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	var_check_sign(char **command, int *is_allocated,
		int *sign_on_end, int *contain_equal)
{
	*sign_on_end = 0;
	if (*command && (*command)[ft_strlen(*command) - 1] == '=')
		*sign_on_end = 1;
	*contain_equal = ft_haschar(*command, '=');
	if (*contain_equal && *sign_on_end && ++*is_allocated)
		*command = ft_strjoin(*command, "''");
	else if (!*contain_equal)
		*command = ft_strjoin(*command, "=''");
}

void	own_export_helper(t_shell *sh, char *command, int is_allocated)
{
	int	i;
	int	sign_on_end;
	int	contain_equal;
	int	var_exist;

	i = -1;
	var_exist = 0;
	while (sh->env[++i])
	{
		if (!ft_strncmp(sh->env[i], command, ft_strlen_until_c(command, '=')))
		{
			var_exist = 1;
			ft_free(sh->env[i]);
			break ;
		}
	}
	var_check_sign(&command, &is_allocated, &sign_on_end, &contain_equal);
	if (contain_equal || !var_exist)
	{
		sh->env[i] = ft_strdup(command);
		if ((!contain_equal && !sign_on_end) || is_allocated)
			free(command);
	}
}

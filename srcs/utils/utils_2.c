/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:14:58 by jsanger           #+#    #+#             */
/*   Updated: 2023/11/25 13:55:20 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_perm_or_file_1(int fd, char *str)
{
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	if (access(str, F_OK | X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	return (0);
}

int	check_perm_or_file_2(int fd, char *str)
{
	if (access(str, F_OK | X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (0);
}

void	deallocate(t_list **root)
{
	t_list	*temp;

	while (*root != NULL)
	{
		temp = *root;
		*root = (*root)->next;
		free(temp);
	}
	free(*root);
	*root = NULL;
}

bool	ft_boolstrchr(const char *s, int c)
{
	unsigned char	a_c;

	a_c = (unsigned char)c;
	while (*s)
	{
		if (*s == a_c)
			return (true);
		s++;
	}
	if (a_c == *s)
		return (true);
	return (false);
}

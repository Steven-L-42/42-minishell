/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_string_infile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:59:17 by slippert          #+#    #+#             */
/*   Updated: 2023/11/24 14:21:12 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cut_string_infile(char *str, int start, int end, char c)
{
	int		length;
	int		removal_length;
	char	*temp;
	int		fd;

	length = strlen(str);
	removal_length = end - start + 1;
	temp = ft_substr(str, start, end - start);
	if (c == '<')
		temp = ft_strtrim_free(temp, " <");
	temp = ft_strtrim_free(temp, "\"\'");
	fd = open(temp, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_putstr_fd(temp, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (free(temp), close(fd), 1);
	}
	close(fd);
	free(temp);
	ft_memmove(str + start, str + end + 1, length - end);
	length -= removal_length;
	str[length + 1] = '\0';
	return (0);
}

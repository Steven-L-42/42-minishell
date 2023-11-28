/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:50:19 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 14:37:27 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	keep_track_of_oldpwd(t_shell *sh)
{
	char	pwd[1024];
	char	**oldpwd;

	getcwd(pwd, sizeof(pwd));
	oldpwd = ft_calloc(3, sizeof(char *));
	oldpwd[0] = ft_strdup("export");
	oldpwd[1] = ft_strjoin("OLDPWD=", pwd);
	own_export(sh, oldpwd, 1);
	free(oldpwd[0]);
	free(oldpwd);
}

void	cd_helper(t_shell *sh, int *error)
{
	if (!ft_strncmp(sh->input, "~~", 2))
		*error = chdir(sh->own_path);
	else if (!ft_strncmp(sh->input, "~/../", 5))
		*error = chdir("/Users");
	else if (!sh->input[0])
		*error = chdir(sh->usr_path);
	else if (sh->input[0] != '$')
		*error = chdir(sh->input);
	if (*error == -1)
	{
		sh->exitcode = 1;
		ft_putstr_fd("cd: ", 2);
		perror(sh->input);
	}
	else
		keep_track_of_oldpwd(sh);
}

void	own_cd(t_shell *sh)
{
	int	error;
	int	count;

	sh->is_builtin = 1;
	count = 2;
	sh->input += 2;
	sh->exitcode = 0;
	while (sh->input[0] == ' ' || sh->input[0] == '\t')
	{
		sh->input += 1;
		count++;
	}
	cd_helper(sh, &error);
	while (count--)
		sh->input -= 1;
}

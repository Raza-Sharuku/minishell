/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_and_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:37:34 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 18:00:54 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

static int	move_to_home(t_env_list **env_list)
{
	t_env_list	*node;

	node = NULL;
	ft_get_env("HOME", *env_list, &node);
	if (node == NULL)
		return (put_error_update_exit_status("cd: HOME not set\n", env_list));
	if (chdir(node->env_str) < 0)
		return (put_error_update_exit_status("chdir", env_list));
	return (SUCCESS);
}

int	cd_cmd(t_word_list *word_list, t_env_list **env_list)
{
	word_list = word_list->next;
	if (word_list == NULL)
		return (move_to_home(env_list));
	if (ft_strcmp(word_list->word, "~") == 0)
		return (move_to_home(env_list));
	if (chdir(word_list->word) < 0)
		return (put_error_update_exit_status(word_list->word, env_list));
	word_list = word_list->next;
	if (word_list != NULL && word_list->flag != pipe_char)
		return (put_error_update_exit_status("cd: too many arguments\n",
				env_list));
	return (SUCCESS);
}

int	pwd_cmd(int fd, int *exit_error_flg)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (change_exit_error_flg(exit_error_flg));
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	free(cwd);
	return (SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:02:22 by reira             #+#    #+#             */
/*   Updated: 2023/08/07 02:35:08 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

void	ft_get_env(char *str, t_env_list *env_list, t_env_list **tmp)
{
	if (env_list == NULL || str == NULL)
		return ;
	while (env_list != NULL && ft_strcmp(env_list->env_name, str) != 0)
		env_list = env_list->next;
	if (env_list != NULL && ft_strcmp(env_list->env_name, str) == 0)
		*tmp = env_list;
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (s1 == NULL)
		return ((unsigned char)s2[0] * -1);
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	get_fd(char *file_name, int flg)
{
	int	fd;

	if (flg == in_file)
		fd = open(file_name, O_RDONLY);
	else if (flg == out_file)
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	else if (flg == heredoc)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	else
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	if (fd < 0)
		return (FAILURE);
	return (fd);
}

int	update_exit_status(t_env_list **env_list, char *estatus)
{
	free((*env_list)->env_value);
	(*env_list)->env_value = ft_strdup(estatus);
	if ((*env_list)->env_value == NULL)
		return (ft_perror("ft_strdup"));
	if (ft_strcmp(estatus, "1") == 0)
		return (FAILURE);
	return (SUCCESS);
}

int	change_exit_flg(int *exit_flg)
{
	*exit_flg = true;
	return (FAILURE);
}

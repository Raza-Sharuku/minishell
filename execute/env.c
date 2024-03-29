/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:06:01 by reira             #+#    #+#             */
/*   Updated: 2023/08/18 04:31:04 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

int	env_cmd(t_env_list **env_list, int fd)
{
	t_env_list	*head;

	head = *env_list;
	*env_list = (*env_list)->next;
	while (*env_list != NULL)
	{
		if ((*env_list)->env_value != NULL)
		{
			ft_putstr_fd((*env_list)->env_name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd((*env_list)->env_value, fd);
			ft_putstr_fd("\n", fd);
		}
		*env_list = (*env_list)->next;
	}
	*env_list = head;
	return (SUCCESS);
}

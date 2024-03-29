/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 00:45:41 by reira             #+#    #+#             */
/*   Updated: 2023/08/18 02:29:35 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

int	cd_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	perror(str);
	return (FAILURE);
}

void	exit_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	exit_err_many_argument(t_env_list **env_list, t_word_list **word_list,
		t_word_list *head)
{
	*word_list = head;
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	return (update_exit_status(env_list, "1"));
}

int	export_error_update_exit_status(char *str, t_env_list **env_list)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	update_exit_status(env_list, "1");
	return (FAILURE);
}

int	env_error_update_exit_status(char *str, t_env_list **env_list)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	update_exit_status(env_list, "127");
	return (FAILURE);
}

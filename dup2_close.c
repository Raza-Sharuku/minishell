/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 02:21:09 by reira             #+#    #+#             */
/*   Updated: 2023/07/31 17:07:16 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

void	dup2_fd_struct(t_fd fd_struct, t_word_list **word_list,
		t_env_list **env_list)
{
	if (fd_struct.in_fd != STDIN_FILENO && dup2(fd_struct.in_fd,
			STDIN_FILENO) < 0)
	{
		ft_perror("dup2");
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	}
	if (fd_struct.out_fd != STDOUT_FILENO && dup2(fd_struct.out_fd,
			STDOUT_FILENO) < 0)
	{
		ft_perror("dup2");
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	}
}

void	dup2_pipe(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (p_data.i == 0)
	{
		if (dup2(p_data.pipe_2darr[p_data.i][WRITE], STDOUT_FILENO) < 0)
			put_error_exit_cmdsver("dup2", p_data, word_list, env_list);
	}
	else if (p_data.i == p_data.cnt)
	{
		if (dup2(p_data.pipe_2darr[p_data.i - 1][READ], STDIN_FILENO) < 0)
			put_error_exit_cmdsver("dup2", p_data, word_list, env_list);
	}
	else
	{
		if (dup2(p_data.pipe_2darr[p_data.i - 1][READ], STDIN_FILENO) < 0)
			put_error_exit_cmdsver("dup2", p_data, word_list, env_list);
		if (dup2(p_data.pipe_2darr[p_data.i][WRITE], STDOUT_FILENO) < 0)
			put_error_exit_cmdsver("dup2", p_data, word_list, env_list);
	}
}

static void	close_first_pipe(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (close(p_data.pipe_2darr[p_data.i][WRITE]) < 0)
		put_error_exit_cmdsver("close", p_data, word_list, env_list);
	if (close(p_data.pipe_2darr[p_data.i][READ]) < 0)
		put_error_exit_cmdsver("close", p_data, word_list, env_list);
}

static void	close_last_pipe(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (close(p_data.pipe_2darr[p_data.i - 1][WRITE]) < 0)
		put_error_exit_cmdsver("close", p_data, word_list, env_list);
	if (close(p_data.pipe_2darr[p_data.i - 1][READ]) < 0)
		put_error_exit_cmdsver("close", p_data, word_list, env_list);
}

void	close_pipe(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (p_data.i == 0)
		close_first_pipe(p_data, word_list, env_list);
	else if (p_data.i == p_data.cnt)
		close_last_pipe(p_data, word_list, env_list);
	else
	{
		close_first_pipe(p_data, word_list, env_list);
		close_last_pipe(p_data, word_list, env_list);
	}
}